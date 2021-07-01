#ifndef SETTINGSCONTROLLER_H
#define SETTINGSCONTROLLER_H

#include <settingsview.h>



class SettingsController
{
public:
    // TODO: Change type of "dataManager" to DataManager once DataManager is defined.
    SettingsController(SettingsView *settingsView, QString *dataManager);

public slots:
    void slot_openSettings();
    void slot_closeSettings();
    void slot_applySettings(int index);
    void slot_applyGlobalSettings(QString projectDir, QString classificationPluginDir, QString imageLoaderPluginsDir);


private:
    SettingsView *settingsView;

    // TODO: Change type of "dataManager" to DataManager once DataManager is defined.
    QString *dataManager;

};

#endif // SETTINGSCONTROLLER_H
