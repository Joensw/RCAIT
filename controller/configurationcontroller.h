#ifndef CONFIGURATIONCONTROLLER_H
#define CONFIGURATIONCONTROLLER_H

#include <QObject>
#include <QMessageBox>
#include "datamanager.h"
#include "configurationdialog.h"


class ConfigurationController : public QObject
{
    Q_OBJECT
public:
    explicit ConfigurationController(QObject *parent = nullptr, DataManager *dataManager = nullptr);
    void verify();
public slots:
    void slot_directoriesSpecified(QString projectDir, QString classificationPluginDir, QString imageLoaderPluginsDir);
signals:
    void sig_configurationComplete();
private:
    ConfigurationDialog *mConfigurationDialog;

    DataManager *mDataManager;
};

#endif // CONFIGURATIONCONTROLLER_H
