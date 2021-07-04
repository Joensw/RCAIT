#ifndef SETTINGSCONTROLLER_H
#define SETTINGSCONTROLLER_H

#include <settingsview.h>
#include <DataManager.h>



class SettingsController
{
public:
    SettingsController(SettingsView *settingsView, DataManager *dataManager);

public slots:
    void slot_openSettings();
    void slot_closeSettings();
    void slot_applySettings(int index);
    void slot_applyGlobalSettings(QString projectDir, QString classificationPluginDir, QString imageLoaderPluginsDir);


private:
    SettingsView *settingsView;

    DataManager *dataManager;

};

#endif // SETTINGSCONTROLLER_H
