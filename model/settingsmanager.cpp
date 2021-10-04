/**
 * @file settingsmanager.cpp
 *
 * @brief functions for managing application and plugin settings
 *
 * @author Jonas Wille
 */
#include "settingsmanager.h"

SettingsManager::SettingsManager()
        : mClassificationPluginManager(&ClassificationPluginManager::getInstance()),
          mImageLoaderPluginManager(&ImageLoaderPluginManager::getInstance()),
          mConfigurationManager(&ConfigurationManager::getInstance()) {

    if (!mConfigurationManager->getClassificationPluginDir().isEmpty() &&
        !mConfigurationManager->getImageLoaderPluginDir().isEmpty()) {
        reload();
    }
}

QStringList SettingsManager::getPluginNames() {
    QStringList loaderPlugins = mImageLoaderPluginManager->getNamesOfPlugins();
    QStringList classifierPlugins = mClassificationPluginManager->getNamesOfPlugins();
    return loaderPlugins + classifierPlugins;
}

QStringList SettingsManager::getClassificationPluginNames() {
    QStringList classifierPlugins = mClassificationPluginManager->getNamesOfPlugins();
    return classifierPlugins;
}

QStringList SettingsManager::getClassificationPluginBase(const QString &plugin) {
    return mClassificationPluginManager->getClassificationPluginBases(plugin);
}

void SettingsManager::reload() {
    mClassificationPluginManager->loadPlugins(mConfigurationManager->getClassificationPluginDir());
    mImageLoaderPluginManager->loadPlugins(mConfigurationManager->getImageLoaderPluginDir());
}

QList<QSharedPointer<QIcon>> SettingsManager::getPluginIcons() {
    auto loaderPluginsIcons = mImageLoaderPluginManager->getPluginIcons();
    auto classifierPluginsIcons = mClassificationPluginManager->getPluginIcons();
    return loaderPluginsIcons + classifierPluginsIcons;
}

QList<QSharedPointer<QWidget>> SettingsManager::getPluginSettings() {
    auto loaderPluginsWidgets = mImageLoaderPluginManager->getConfigurationWidgets();
    auto classifierPluginsWidgets = mClassificationPluginManager->getConfigurationWidgets();
    return loaderPluginsWidgets + classifierPluginsWidgets;
}

void SettingsManager::savePluginSettings(const int &index) {
    QStringList loaderPlugins = mImageLoaderPluginManager->getNamesOfPlugins();
    qsizetype loaderSize = loaderPlugins.size();
    QStringList classifierPlugins = mClassificationPluginManager->getNamesOfPlugins();
    loaderPlugins.append(classifierPlugins);
    QString name = loaderPlugins.at(index);

    if (index < loaderSize) {
        mImageLoaderPluginManager->saveConfiguration(name);
    } else
        mClassificationPluginManager->saveConfiguration(name);
}

bool
SettingsManager::applyGlobalSettings(const QString &projectsDir, const QString &classificationPluginDir,
                                     const QString &imageLoaderPluginDir, const QString &pythonPath,
                                     QString &error, int &pathsChanged) {
    int pathsChangedCounter = 0;
    QString tempProjectsDir = mConfigurationManager->getProjectsDir();
    QString tempClassificationPluginDir = mConfigurationManager->getClassificationPluginDir();
    QString tempImageLoaderPluginDir = mConfigurationManager->getImageLoaderPluginDir();
    QString tempPythonPath = mConfigurationManager->getPythonExecutablePath();

    //Check if there is an actual update to any of the paths
    if (!projectsDir.isEmpty()) {
        pathsChangedCounter++;
        tempProjectsDir = projectsDir;
    }
    if (!classificationPluginDir.isEmpty()) {
        pathsChangedCounter++;
        tempClassificationPluginDir = classificationPluginDir;
    }
    if (!imageLoaderPluginDir.isEmpty()) {
        pathsChangedCounter++;
        tempImageLoaderPluginDir = imageLoaderPluginDir;
    }
    if (!pythonPath.isEmpty()) {
        pathsChangedCounter++;
        tempPythonPath = pythonPath;
    }

    //check if all paths are allowed and if any of them are overlapping
    if (ConfigurationManager::verifyPaths(
            {tempProjectsDir, tempClassificationPluginDir, tempImageLoaderPluginDir, tempPythonPath})) {
        mConfigurationManager->saveProjectsDir(tempProjectsDir);
        saveClassificationPluginDir(tempClassificationPluginDir);
        saveImageLoaderPluginDir(tempImageLoaderPluginDir);
        mConfigurationManager->savePythonPath(tempPythonPath);

        pathsChanged = pathsChangedCounter;

        return true;

    }

    error = ERROR_CONFLICT;
    pathsChanged = 0;

    return false;
}

QStringList SettingsManager::getImageLoaderPluginNames() {
    return mImageLoaderPluginManager->getNamesOfPlugins();
}

void SettingsManager::saveClassificationPluginDir(const QString &dir) {
    mConfigurationManager->saveClassificationPluginDir(dir);
    SettingsManager::mClassificationPluginManager->loadPlugins(dir);
}

void SettingsManager::saveImageLoaderPluginDir(const QString &dir) {
    mConfigurationManager->saveImageLoaderPluginDir(dir);
    SettingsManager::mImageLoaderPluginManager->loadPlugins(dir);
}
