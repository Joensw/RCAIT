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
    void loadSettings() const;

    /**
     * @brief getAPIKey gets the API Key
     * @return the API Key
     */
    QString getAPIKey() const;

    /**
     * @brief getAPISecret gets the API secret
     * @return the API secret
     */
    QString getAPISecret() const;
    /**
     * @brief getPythonPath gets the path of the python executable
     * @return the python executable path
     */
    QString getPythonPath() const;

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

    /**
     * @brief isConfigured checks if all settings have been set
     * @return true if set
     */
    bool isConfigured();

    /**
     * @brief getConfigError returns a short error message for missing configuration
     * @return the error message
     */
    QString getMissingConfigError() const;

private:
    Ui::FlickrSettings *ui;
    QString m_apiKey = "API Key";
    QString m_apiSecret = "API Secret";
    QString m_pythonPath = "Python Path";
    QSettings m_settings = {"Flickr Plugin",QSettings::IniFormat};
    QString m_errorMessage;
    inline static const QString ERROR_STRING = "Error: ";
    inline static const QString ERROR_END = " not set.";
    inline static const QString CONFIGURED_STRING = "All settings are set.";

};

#endif // FLICKRSETTINGS_H
