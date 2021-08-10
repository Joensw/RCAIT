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
    /**
     * @brief saveSettings saves the settings
     */
    void saveSettings();
    /**
     * @brief loadSettings loads the settings from the persistent storage
     */
    void loadSettings();
    /**
     * @brief getaAPIKey gets the API Key
     * @return the API Key
     */
    QString getaAPIKey();
    /**
     * @brief getAPISecret get the API secret
     * @return the API secret
     */
    QString getAPISecret();
    /**
     * @brief getPythonPath gets the path of the python executable
     * @return the python executable path
     */
    QString getPythonPath();

private:
    Ui::FlickrSettings *ui;
    QString m_apiKey = "API Key";
    QString m_apiSecret = "API Secret";
    QString m_pythonPath = "Python Path";
    QSettings m_settings = {"Flickr Plugin",QSettings::IniFormat};

};

#endif // FLICKRSETTINGS_H
