#include "settingsmanager.h"


const QString projectDirectoryIdentifier = "ProjectDirectory";
const QString classificationPluginDirectoryIdentifier = "ClassificationPluginPath";
const QString imageLoaderPluginDirectoryIdentifier = "ImageLoaderPluginPath";

SettingsManager::SettingsManager()
        : mClassificationPluginManager(&ClassificationPluginManager::getInstance()),
          mImageLoaderPluginManager(&ImageLoaderPluginManager::getInstance()) {

    mGlobalSettings.reset(new QSettings);
    mClassificationPluginManager->loadPlugins(getClassificationPluginDir());
    mImageLoaderPluginManager->loadPlugins(getImageLoaderPluginDir());
}

QStringList SettingsManager::getPluginNames() {
    QStringList loaderPlugins = mImageLoaderPluginManager->getNamesOfPlugins();
    QStringList classifierPlugins = mClassificationPluginManager->getNamesOfPlugins();
    loaderPlugins.append(classifierPlugins);
    return loaderPlugins;
}

QStringList SettingsManager::getClassificationPluginNames() {
    QStringList classifierPlugins = mClassificationPluginManager->getNamesOfPlugins();
    return classifierPlugins;
}

QStringList SettingsManager::getClassificationPluginBase(QString plugin) {
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

bool SettingsManager::verifyPaths(QString projectsDirectory, QString classificationPluginDirectory,
                                  QString imageLoaderDirectory) {
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

bool SettingsManager::verifyPath(QString path) {
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

void SettingsManager::configureSettingsFile(QString projectsDirectory, QString classificationPluginDirectory,
                                            QString imageLoaderDirectory) {
    mGlobalSettings->setValue(projectDirectoryIdentifier, projectsDirectory);
    mGlobalSettings->setValue(classificationPluginDirectoryIdentifier, classificationPluginDirectory);
    mGlobalSettings->setValue(imageLoaderPluginDirectoryIdentifier, imageLoaderDirectory);
}

QList<QWidget *> SettingsManager::getPluginSettings() {
    QList<QWidget *> loaderPluginsWidgets = mImageLoaderPluginManager->getConfigurationWidgets();
    QList<QWidget *> classifierPluginsWidgets = mClassificationPluginManager->getConfigurationWidgets();
    loaderPluginsWidgets.append(classifierPluginsWidgets);
    return loaderPluginsWidgets;
}

void SettingsManager::savePluginSettings(int index) {
    QStringList loaderPlugins = mImageLoaderPluginManager->getNamesOfPlugins();
    int loaderSize = loaderPlugins.size();
    QStringList classifierPlugins = mClassificationPluginManager->getNamesOfPlugins();
    loaderPlugins.append(classifierPlugins);
    QString name = loaderPlugins.at(index);

    if (index < loaderSize) {
        mImageLoaderPluginManager->saveConfiguration(name);
    } else
        mClassificationPluginManager->saveConfiguration(name);
}

void SettingsManager::saveProjectsDir(QString dir) {
    mGlobalSettings->setValue(projectDirectoryIdentifier, dir);
}

QString SettingsManager::getProjectsDir() {
    return mGlobalSettings->value(projectDirectoryIdentifier).toString();
}

void SettingsManager::saveClassificationPluginDir(QString dir) {
    mGlobalSettings->setValue(classificationPluginDirectoryIdentifier, dir);
    mClassificationPluginManager->loadPlugins(dir);
}

QString SettingsManager::getClassificationPluginDir() {
    return mGlobalSettings->value(classificationPluginDirectoryIdentifier).toString();
}

void SettingsManager::saveImageLoaderPluginDir(QString dir) {
    mGlobalSettings->setValue(imageLoaderPluginDirectoryIdentifier, dir);
    mImageLoaderPluginManager->loadPlugins(dir);
}

QString SettingsManager::getImageLoaderPluginDir() {
    return mGlobalSettings->value(imageLoaderPluginDirectoryIdentifier).toString();
}

bool
SettingsManager::applyGlobalSettings(QString projectsDir, QString classificationPluginDir, QString imageLoaderPluginDir,
                                     QString *error, int *pathsChanged) {

    int pathsChangedTemp = 0;
    QString tempProjectsDir = getProjectsDir();
    QString tempClassificationPluginDir = getClassificationPluginDir();
    QString tempImageLoaderPluginDir = getImageLoaderPluginDir();


    //Check if there is an actual update to any of the paths
    if (!projectsDir.isEmpty()) {
        pathsChangedTemp++;
        tempProjectsDir = projectsDir;
    }
    if (!classificationPluginDir.isEmpty()) {
        pathsChangedTemp++;
        tempClassificationPluginDir = classificationPluginDir;
    }
    if (!imageLoaderPluginDir.isEmpty()) {
        pathsChangedTemp++;
        tempImageLoaderPluginDir = imageLoaderPluginDir;
    }

    //check if all paths are allowed and if any of them are overlapping
    if (verifyPaths(tempProjectsDir, tempClassificationPluginDir, tempImageLoaderPluginDir)) {
        saveProjectsDir(tempProjectsDir);
        saveClassificationPluginDir(tempClassificationPluginDir);
        saveImageLoaderPluginDir(tempImageLoaderPluginDir);

        if (pathsChanged != nullptr) {
            *pathsChanged = pathsChangedTemp;
        }
        return true;

    }
    if (error != nullptr) {
        *error = QObject::tr(
                "Settings have not been updated, there is a conflict. \n Paths may not be identical and must exist, this includes new and unchanged paths.");
    }
    if (pathsChanged != nullptr) {
        *pathsChanged = 0;
    }
    return false;
}

QStringList SettingsManager::getImageLoaderPluginNames() {
    return mImageLoaderPluginManager->getNamesOfPlugins();
}
