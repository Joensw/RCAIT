#ifndef SETTINGSVIEW_H
#define SETTINGSVIEW_H

#include <QWidget>

class SettingsView : public QWidget
{
    Q_OBJECT
public:
    explicit SettingsView(QWidget *parent = nullptr);
    SettingsView(QWidget *parent, QStringList pluginNames, QList<QWidget*> pluginConfigurationWidgets);

signals:
    void sig_applyGlobalSettings(QString projectsDir, QString classificationPluginsDir, QString imageLoaderPlugins);
    void sig_applySettings(int index);
    void sig_closeSettings();
};

#endif // SETTINGSVIEW_H
