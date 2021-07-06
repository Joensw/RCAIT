#ifndef SETTINGSVIEW_H
#define SETTINGSVIEW_H

#include <QWidget>

namespace Ui {
class SettingsView;
}

class SettingsView : public QWidget
{
    Q_OBJECT


public:
    explicit SettingsView(QWidget *parent = nullptr);
    ~SettingsView();
    SettingsView(QWidget *parent, QStringList pluginNames, QList<QWidget*> pluginConfigurationWidgets);


signals:
    void sig_applyGlobalSettings(QString projectsDir, QString classificationPluginsDir, QString imageLoaderPlugins);
    void sig_applySettings(int index);
    void sig_closeSettings();

private slots:
    void on_saveButton_clicked();

private:
    Ui::SettingsView *ui;
    QWidget* mGlobalSettingsWidget;
};

#endif // SETTINGSVIEW_H
