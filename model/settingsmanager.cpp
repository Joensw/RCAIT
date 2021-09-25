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

QStringList SettingsManager::getClassificationPluginBase(const QString &plugin) {
    return mClassificationPluginManager->getClassificationPluginBases(plugin);
}

bool SettingsManager::verifyDirectories() {
    if (mGlobalSettings->contains(projectDirectoryIdentifier)
        && mGlobalSettings->contains(classificationPluginDirectoryIdentifier)
        && mGlobalSettings->contains(imageLoaderPluginDirectoryIdentifier)
        && mGlobalSettings->contains(pythonExecutablePathIdentifier)) {
        //All keys exist and have values

        QString projectPath = mGlobalSettings->value(projectDirectoryIdentifier).toString();
        QString classificationPath = mGlobalSettings->value(classificationPluginDirectoryIdentifier).toString();
        QString imageLoaderPath = mGlobalSettings->value(imageLoaderPluginDirectoryIdentifier).toString();
        QString pythonPath = mGlobalSettings->value(pythonExecutablePathIdentifier).toString();

        return verifyPaths({projectPath, classificationPath, imageLoaderPath, pythonPath});
    }
    //Settings file wasn't complete
    return false;
}

bool SettingsManager::verifyPaths(const QStringList &paths) {
    //Check for duplicates
    if (QSet<QString>(paths.begin(), paths.end()).size() != paths.size()) return false;

    //QDir treats the "" directory as "." and will always return true on .exists();
    if (paths.contains("")) return false;

    //Check if all paths exist
    return std::all_of(paths.begin(), paths.end(), [](const QString &path) { return QDir(path).exists(); });
}

void
SettingsManager::configureSettingsFile(const QString &projectsDirectory, const QString &classificationPluginDirectory,
                                       const QString &imageLoaderDirectory) {
    mGlobalSettings->setValue(projectDirectoryIdentifier, projectsDirectory);
    mGlobalSettings->setValue(classificationPluginDirectoryIdentifier, classificationPluginDirectory);
    mGlobalSettings->setValue(imageLoaderPluginDirectoryIdentifier, imageLoaderDirectory);
}

void SettingsManager::reload() {
    mClassificationPluginManager->loadPlugins(getClassificationPluginDir());
    mImageLoaderPluginManager->loadPlugins(getImageLoaderPluginDir());
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

void SettingsManager::saveProjectsDir(const QString &dir) {
    mGlobalSettings->setValue(projectDirectoryIdentifier, dir);
}

QString SettingsManager::getProjectsDir() {
    return mGlobalSettings->value(projectDirectoryIdentifier).toString();
}

void SettingsManager::saveClassificationPluginDir(const QString &dir) {
    mGlobalSettings->setValue(classificationPluginDirectoryIdentifier, dir);
    mClassificationPluginManager->loadPlugins(dir);
}

QString SettingsManager::getClassificationPluginDir() {
    return mGlobalSettings->value(classificationPluginDirectoryIdentifier).toString();
}

void SettingsManager::saveImageLoaderPluginDir(const QString &dir) {
    mGlobalSettings->setValue(imageLoaderPluginDirectoryIdentifier, dir);
    mImageLoaderPluginManager->loadPlugins(dir);
}

void SettingsManager::savePythonPath(const QString &path) {
    mGlobalSettings->setValue(pythonExecutablePathIdentifier, path);
}

QString SettingsManager::getImageLoaderPluginDir() {
    return mGlobalSettings->value(imageLoaderPluginDirectoryIdentifier).toString();
}

QString SettingsManager::getPythonExecutablePath() {
    return mGlobalSettings->value(pythonExecutablePathIdentifier).toString();
}

bool
SettingsManager::applyGlobalSettings(const QString &projectsDir, const QString &classificationPluginDir,
                                     const QString &imageLoaderPluginDir, const QString &pythonPath,
                                     QString *error, int *pathsChanged) {

    int pathsChangedCounter = 0;
    QString tempProjectsDir = getProjectsDir();
    QString tempClassificationPluginDir = getClassificationPluginDir();
    QString tempImageLoaderPluginDir = getImageLoaderPluginDir();
    QString tempPythonPath = getPythonExecutablePath();

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
    if (verifyPaths({tempProjectsDir, tempClassificationPluginDir, tempImageLoaderPluginDir, tempPythonPath})) {
        saveProjectsDir(tempProjectsDir);
        saveClassificationPluginDir(tempClassificationPluginDir);
        saveImageLoaderPluginDir(tempImageLoaderPluginDir);
        savePythonPath(tempPythonPath);

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
