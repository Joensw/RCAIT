/**
 * @file configurationmanager.cpp
 *
 * @brief functions for managing (basic) application and plugin settings
 *
 * @author Jonas Wille
 */
#include "configurationmanager.h"

ConfigurationManager::ConfigurationManager()
        : mGlobalSettings(new QSettings) {
}

bool ConfigurationManager::verifyDirectories() {
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

bool ConfigurationManager::verifyPaths(const QStringList &paths) {
    //Check for duplicates
    if (QSet<QString>(paths.begin(), paths.end()).size() != paths.size()) return false;

    //QDir treats the "" directory as "." and will always return true on .exists();
    if (paths.contains("")) return false;

    //Check if all paths exist
    return std::all_of(paths.begin(), paths.end(), [](const QString &path) { return QFileInfo::exists(path); });
}

void
ConfigurationManager::configureSettingsFile(const QString &projectsDirectory,
                                            const QString &classificationPluginDirectory,
                                            const QString &imageLoaderDirectory, const QString &pythonPath) const {
    mGlobalSettings->setValue(projectDirectoryIdentifier, projectsDirectory);
    mGlobalSettings->setValue(classificationPluginDirectoryIdentifier, classificationPluginDirectory);
    mGlobalSettings->setValue(imageLoaderPluginDirectoryIdentifier, imageLoaderDirectory);
    mGlobalSettings->setValue(pythonExecutablePathIdentifier, pythonPath);

    qDebug() << pythonPath;
}

void ConfigurationManager::saveProjectsDir(const QString &dir) const {
    mGlobalSettings->setValue(projectDirectoryIdentifier, dir);
}

QString ConfigurationManager::getProjectsDir() const {
    return mGlobalSettings->value(projectDirectoryIdentifier).toString();
}

void ConfigurationManager::saveClassificationPluginDir(const QString &dir) const {
    mGlobalSettings->setValue(classificationPluginDirectoryIdentifier, dir);
}

QString ConfigurationManager::getClassificationPluginDir() const {
    return mGlobalSettings->value(classificationPluginDirectoryIdentifier).toString();
}

void ConfigurationManager::saveImageLoaderPluginDir(const QString &dir) const {
    mGlobalSettings->setValue(imageLoaderPluginDirectoryIdentifier, dir);
}

void ConfigurationManager::savePythonPath(const QString &path) const {
    mGlobalSettings->setValue(pythonExecutablePathIdentifier, path);
}

QString ConfigurationManager::getImageLoaderPluginDir() const {
    return mGlobalSettings->value(imageLoaderPluginDirectoryIdentifier).toString();
}

QString ConfigurationManager::getPythonExecutablePath() const {
    auto value = mGlobalSettings->value(pythonExecutablePathIdentifier);
    return value.isNull() ? PYTHON_FALLBACK : value.toString();
}