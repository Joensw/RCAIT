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
          mImageLoaderPluginManager(&ImageLoaderPluginManager::getInstance()) {

    mGlobalSettings.reset(new QSettings);
    if (!getClassificationPluginDir().isEmpty() && !getImageLoaderPluginDir().isEmpty()) {
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

QStringList SettingsManager::getClassificationPluginBase(const QString& plugin) {
    return mClassificationPluginManager->getClassificationPluginBases(plugin);
}

bool SettingsManager::verifyDirectories() {
    if (mGlobalSettings->contains(projectDirectoryIdentifier)
        && mGlobalSettings->contains(classificationPluginDirectoryIdentifier)
        && mGlobalSettings->contains(imageLoaderPluginDirectoryIdentifier)) {
        //All keys exist and have values

        QString projectPath = mGlobalSettings->value(projectDirectoryIdentifier).toString();
        QString classificationPath = mGlobalSettings->value(classificationPluginDirectoryIdentifier).toString();
        QString imageLoaderPath = mGlobalSettings->value(imageLoaderPluginDirectoryIdentifier).toString();

        return verifyPaths(projectPath, classificationPath, imageLoaderPath);
    }
    //Settings file wasnt complete
    return false;
}

bool SettingsManager::verifyPaths(const QString& projectsDirectory, const QString& classificationPluginDirectory,
                                  const QString& imageLoaderDirectory) {
    if (projectsDirectory == classificationPluginDirectory ||
        projectsDirectory == imageLoaderDirectory ||
        classificationPluginDirectory == imageLoaderDirectory) {
        return false;
    }

    //QDir treats the "" directory as "." and will always return true on .exists();
    if (projectsDirectory.isEmpty() || classificationPluginDirectory.isEmpty() || imageLoaderDirectory.isEmpty()) {
        return false;
    }

    QDir projectDir = QDir(projectsDirectory);
    QDir classificationDir = QDir(classificationPluginDirectory);
    QDir imageLoaderDir = QDir(imageLoaderDirectory);

    if (projectDir.exists() && classificationDir.exists() && imageLoaderDir.exists()) {
        return true;
    }
    return false;
}

bool SettingsManager::verifyPath(const QString& path) {
    //Null and empty string are not valid paths
    if (path.isEmpty()) {
        return false;
    }
    QDir directory = QDir(path);

    if (directory.exists()) {
        return true;
    }
    return false;
}

void SettingsManager::configureSettingsFile(const QString& projectsDirectory, const QString& classificationPluginDirectory,
                                            const QString& imageLoaderDirectory) {
    mGlobalSettings->setValue(projectDirectoryIdentifier, projectsDirectory);
    mGlobalSettings->setValue(classificationPluginDirectoryIdentifier, classificationPluginDirectory);
    mGlobalSettings->setValue(imageLoaderPluginDirectoryIdentifier, imageLoaderDirectory);
}

void SettingsManager::reload()
{
    mClassificationPluginManager->loadPlugins(getClassificationPluginDir());
    mImageLoaderPluginManager->loadPlugins(getImageLoaderPluginDir());
}

QList<QSharedPointer<QIcon> > SettingsManager::getPluginIcons()
{
    auto loaderPluginsWidgets = mImageLoaderPluginManager->getPluginIcons();
    auto classifierPluginsWidgets = mClassificationPluginManager->getPluginIcons();
    return loaderPluginsWidgets + classifierPluginsWidgets;
}

QList<QSharedPointer<QWidget>> SettingsManager::getPluginSettings() {
    auto loaderPluginsWidgets = mImageLoaderPluginManager->getConfigurationWidgets();
    auto classifierPluginsWidgets = mClassificationPluginManager->getConfigurationWidgets();
    return loaderPluginsWidgets + classifierPluginsWidgets;
}

void SettingsManager::savePluginSettings(int index) {
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

void SettingsManager::saveProjectsDir(const QString& dir) {
    mGlobalSettings->setValue(projectDirectoryIdentifier, dir);
}

QString SettingsManager::getProjectsDir() {
    return mGlobalSettings->value(projectDirectoryIdentifier).toString();
}

void SettingsManager::saveClassificationPluginDir(const QString& dir) {
    mGlobalSettings->setValue(classificationPluginDirectoryIdentifier, dir);
    mClassificationPluginManager->loadPlugins(dir);
}

QString SettingsManager::getClassificationPluginDir() {
    return mGlobalSettings->value(classificationPluginDirectoryIdentifier).toString();
}

void SettingsManager::saveImageLoaderPluginDir(const QString& dir) {
    mGlobalSettings->setValue(imageLoaderPluginDirectoryIdentifier, dir);
    mImageLoaderPluginManager->loadPlugins(dir);
}

QString SettingsManager::getImageLoaderPluginDir() {
    return mGlobalSettings->value(imageLoaderPluginDirectoryIdentifier).toString();
}

bool
SettingsManager::applyGlobalSettings(const QString& projectsDir, const QString& classificationPluginDir, const QString& imageLoaderPluginDir,
                                     QString *error, int *pathsChanged) {

    int pathsChangedCounter = 0;
    QString tempProjectsDir = getProjectsDir();
    QString tempClassificationPluginDir = getClassificationPluginDir();
    QString tempImageLoaderPluginDir = getImageLoaderPluginDir();

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

    //check if all paths are allowed and if any of them are overlapping
    if (verifyPaths(tempProjectsDir, tempClassificationPluginDir, tempImageLoaderPluginDir)) {
        saveProjectsDir(tempProjectsDir);
        saveClassificationPluginDir(tempClassificationPluginDir);
        saveImageLoaderPluginDir(tempImageLoaderPluginDir);

        if (pathsChanged != nullptr) {
            *pathsChanged = pathsChangedCounter;
        }
        return true;

    }
    if (error != nullptr) {
        *error = ERROR_CONFLICT;
    }
    if (pathsChanged != nullptr) {
        *pathsChanged = 0;
    }
    return false;
}

QStringList SettingsManager::getImageLoaderPluginNames() {
    return mImageLoaderPluginManager->getNamesOfPlugins();
}
