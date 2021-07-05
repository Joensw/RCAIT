#ifndef SETTINGS_H
#define SETTINGS_H

#include "imageloaderplugin.h"
#include <QWidget>

namespace Ui {
class Settings;
}

class Settings : public QWidget
{
    Q_OBJECT


public:
    explicit Settings(QWidget *parent = nullptr, ImageLoaderPlugin *plugin = nullptr);
    QString addSettings(QString name, QWidget *settingsWidget);
    ~Settings();

private slots:
    void on_pushButton_clicked();

private:
    Ui::Settings *ui;
    QWidgetList pluginSettings;
    ImageLoaderPlugin *plugin;
    void saveSettings();
};

#endif // SETTINGS_H
