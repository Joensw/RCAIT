#ifndef SETTINGS_H
#define SETTINGS_H

#include "echointerface.h"
#include <QWidget>

namespace Ui {
class Settings;
}

class Settings : public QWidget
{
    Q_OBJECT


public:
    explicit Settings(QWidget *parent = nullptr, EchoInterface *plugin = nullptr);
    QString addSettings(QString name, QWidget *settingsWidget);
    ~Settings();

private slots:
    void on_pushButton_clicked();

private:
    Ui::Settings *ui;
    QWidgetList pluginSettings;
    EchoInterface *plugin;
    void saveSettings();
};

#endif // SETTINGS_H
