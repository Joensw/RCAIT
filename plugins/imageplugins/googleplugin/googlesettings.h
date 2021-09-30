/**
 * @file Googlesettings.h
 *
 * @brief contains class GoogleSettings
 */
#ifndef GoogleSETTINGS_H
#define GoogleSETTINGS_H

#include <QWidget>
#include <QSettings>
#include <QtCore>

namespace Ui {
class GoogleSettings;
}
/**
 * @brief The GoogleSettings class for persistently storing settings of GooglePlugin class
 */
class GoogleSettings : public QWidget
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
     * @brief GoogleSettings constructor
     * @param parent widget
     */
    explicit GoogleSettings(QWidget *parent = nullptr);
    /**
     * @brief GoogleSettings destructor
     */
    ~GoogleSettings();
    /**
     * @brief saveSettings safes the settings
     */
    void saveSettings();
    /**
     * @brief loadSettings loads the settings
     */
    void loadSettings();
    /**
     * @brief getPythonPath gets the Path of the python executable
     * @return the python path
     */
    QString getPythonPath();

    /**
     * @brief setPythonPath sets the Python path
     * @param path the path
     */
    void setPythonPath(QString path);

    /**
     * @brief getAPIKey gets the API Key
     * @return the API Key
     */
    QString getAPIKey();

    /**
     * @brief getProjectCX gets the Project CX of the Google API, see https://cse.google.com/cse/all
     * @return the project CX
     */
    QString getProjectCX();

    /**
     * @brief isConfigured checks if all settings have been set
     * @return true if set
     */
    bool isConfigured();

    /**
     * @brief getConfigError returns a short error message for missing configuration
     * @return the error message
     */
    QString getMissingConfigError();


private:
    Ui::GoogleSettings *ui;
    QString m_pythonPath = "Python Path";
    QString m_projectCX = "Project CX";
    QString m_APIKey = "API Key";
    QSettings m_settings = {"Google Plugin",QSettings::IniFormat};
    QString m_errorMessage;
    inline static const QString ERROR_STRING = "Error: ";
    inline static const QString ERROR_END = " not set.";
    inline static const QString CONFIGURED_STRING = "All settings are set.";
};

#endif // GoogleSETTINGS_H
