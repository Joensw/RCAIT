#ifndef BINGSETTINGS_H
#define BINGSETTINGS_H

#include <QWidget>
#include <QSettings>
#include <QtCore>

namespace Ui {
class BingSettings;
}

class BingSettings : public QWidget
{
    Q_OBJECT

public:
    explicit BingSettings(QWidget *parent = nullptr);
    ~BingSettings();
    void saveSettings();
    void loadSettings();
    QString getaAPIKey();
    QString getAPISecret();
    QString getPythonPath();


    QSettings m_settings = {"Bing Plugin",QSettings::IniFormat};


private:
    Ui::BingSettings *ui;
    QString m_apiKey = "API Key";
    QString m_apiSecret = "API Secret";
    QString m_pythonPath = "Python Path";
};

#endif // BINGSETTINGS_H
