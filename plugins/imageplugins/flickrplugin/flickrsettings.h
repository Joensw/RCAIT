/**
 * @file flickrsettings.h
 *
 * @brief saves settings for the FlickrPlugin class persistently
 *
 */
#ifndef FLICKRSETTINGS_H
#define FLICKRSETTINGS_H

#include <QWidget>
#include <QSettings>
#include <QtCore>

namespace Ui {
class FlickrSettings;
}
/**
 *@brief the FlickrSettingsclass
 */
class FlickrSettings : public QWidget
{
    Q_OBJECT

protected:

    /**
     * @brief changeEvent event handler
     *
     * @param event incoming event
     */
    void changeEvent(QEvent *event) override;

public:
    /**
     * @brief FlickrSettings constructor
     * @param parent the parent widget
     */
    explicit FlickrSettings(QWidget *parent = nullptr);
    /**
     * @brief FlickrSettings destructor
     */
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
     * @brief getAPIKey gets the API Key
     * @return the API Key
     */
    QString getAPIKey();

    /**
     * @brief getAPISecret gets the API secret
     * @return the API secret
     */
    QString getAPISecret();
    /**
     * @brief getPythonPath gets the path of the python executable
     * @return the python executable path
     */
    QString getPythonPath();

    /**
     * @brief setAPIKey sets the API Key
     * @param key API Key
     */
    void setAPIKey(QString key);

    /**
     * @brief setAPISecret sets the API secret
     * @param key API Key
     */
    void setAPISecret(QString key);

    /**
     * @brief setPythonPath sets the Python path
     * @param path the path
     */
    void setPythonPath(QString path);

private:
    Ui::FlickrSettings *ui;
    QString m_apiKey = "API Key";
    QString m_apiSecret = "API Secret";
    QString m_pythonPath = "Python Path";
    QSettings m_settings = {"Flickr Plugin",QSettings::IniFormat};

};

#endif // FLICKRSETTINGS_H
