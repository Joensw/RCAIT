#ifndef SETTINGSVIEW_H
#define SETTINGSVIEW_H

#include <QDialog>

namespace Ui {
class SettingsView;
}

class SettingsView : public QDialog
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
    void on_applyButton_clicked();

    void on_pluginList_clicked(const QModelIndex &index);

    void on_closeButton_clicked();

private:
    Ui::SettingsView *ui;
    int mCurrIndex;
    QList<QWidget*> mPluginWidgets;
    QWidget* mGlobalSettingsWidget;

};

#endif // SETTINGSVIEW_H
