#ifndef FLICKRSETTINGS_H
#define FLICKRSETTINGS_H

#include <QWidget>
#include <QSettings>
#include <QtCore>

namespace Ui {
class FlickrSettings;
}

class FlickrSettings : public QWidget
{
    Q_OBJECT

public:
    explicit FlickrSettings(QWidget *parent = nullptr);
    ~FlickrSettings();
    void saveSettings();
    void loadSettings();
    QString getaAPIKey();
    QString getAPISecret();
    QString getPythonPath();

private:
    Ui::FlickrSettings *ui;
    QString m_apiKey = "API Key";
    QString m_apiSecret = "API Secret";
    QString m_pythonPath = "Python Path";
    QSettings m_settings = {"Flickr Plugin",QSettings::IniFormat};

};

#endif // FLICKRSETTINGS_H
