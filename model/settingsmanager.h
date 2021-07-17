#ifndef SETTINGSMANAGER_H
#define SETTINGSMANAGER_H

#include <QString>
#include <QWidget>
#include <QSettings>

#include "classificationpluginmanager.h"
#include "imageloaderpluginmanager.h"

extern const QString GLOBAL_SETTINGS_LOCATION;


class SettingsManager
{
public:
    SettingsManager();

    QStringList getPluginNames();
    QList<QWidget*> getPluginSettings();
    void savePluginSettings(int index);
    void saveProjectsDir(QString value);
    QString getProjectsDir();
    void saveClassificationPluginDir(QString value);
    QString getClassificationPluginDir();
    void saveImageLoaderPluginDir(QString value);
    QString getImageLoaderPluginDir();

    QStringList getClassificationPluginNames();
    QStringList getClassificationPluginBase(QString basesOf);

    bool verifyDirectories();
    bool verifyPaths(QString projectsDirectory, QString classificationPluginDirectory, QString imageLoaderDirectory);
    bool verifyPath(QString path);

private:
    ClassificationPluginManager * mClassificationPluginManager;
    ImageLoaderPluginManager * mImageLoaderPluginManager;


    QSettings * mGlobalSettings;



};

#endif // SETTINGSMANAGER_H
