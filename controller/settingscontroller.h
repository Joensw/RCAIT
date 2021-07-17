#ifndef SETTINGSCONTROLLER_H
#define SETTINGSCONTROLLER_H

#include <QMessageBox>

#include <settingsview.h>
#include <datamanager.h>
#include "configurationdialog.h"




class SettingsController : public QObject
{
    Q_OBJECT
public:
    // SettingsController besorgt sich ja erst alle Informationen, die nötig sind um ein (sinvolles) SettingsView zu erstellen,
    // daher wird kein SettingsView mitgegeben sondern erst hier erzeugt
    explicit SettingsController(QObject *parent = nullptr, DataManager *dataManager = nullptr);


public slots:
    void slot_openSettings();

    void slot_applySettings(int index);
    void slot_applyGlobalSettings(QString projectDir, QString classificationPluginDir, QString imageLoaderPluginsDir);

signals:
    void sig_projectDirectoryChanged();

private:
    SettingsView *mSettingsView;

    DataManager *mDataManager;

};

#endif // SETTINGSCONTROLLER_H
