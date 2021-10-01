/**
 * @file bingsettings.h
 *
 * @brief contains class BingSettings
 */
#ifndef BINGSETTINGS_H
#define BINGSETTINGS_H

#include <QWidget>
#include <QSettings>
#include <QtCore>

namespace Ui {
class BingSettings;
}
/**
 * @brief The BingSettings class for persistently storing settings of BingPlugin class
 */
class BingSettings : public QWidget
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
     * @brief BingSettings constructor
     * @param parent widget
     */
    explicit BingSettings(QWidget *parent = nullptr);
    /**
     * @brief BingSettings destructor
     */
    ~BingSettings();
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
    Ui::BingSettings *ui;
    QString m_pythonPath = "Python Path";
    QSettings m_settings = {"Bing Plugin",QSettings::IniFormat};
    QString m_errorMessage;
    inline static const QString NOT_CONFIGURED_STRING = "Error: Python executable path is not set.";
    inline static const QString CONFIGURED_STRING = "Python executable path is set.";
};

#endif // BINGSETTINGS_H
