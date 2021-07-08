#ifndef SETTINGSMANAGER_H
#define SETTINGSMANAGER_H

#include <QString>
#include <QWidget>
#include <QSettings>

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







private:
    QSettings mGlobalSettings;


};

#endif // SETTINGSMANAGER_H
