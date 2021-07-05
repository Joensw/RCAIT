#ifndef SETTINGSCONTROLLER_H
#define SETTINGSCONTROLLER_H

#include <datamanager.h>
#include <settingsview.h>
#include <datamanager.h>



class SettingsController
{
public:
    SettingsController(SettingsView *settingsView, DataManager *dataManager);

public slots:
    // probably useless
        void slot_openSettings();
        void slot_closeSettings();
    // probably useless

    void slot_applySettings(int index);
    void slot_applyGlobalSettings(QString projectDir, QString classificationPluginDir, QString imageLoaderPluginsDir);


private:
    SettingsView *settingsView;

    DataManager *dataManager;

};

#endif // SETTINGSCONTROLLER_H
