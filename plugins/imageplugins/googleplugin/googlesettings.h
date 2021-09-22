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



private:
    Ui::GoogleSettings *ui;
    QString m_pythonPath = "Python Path";
    QString m_projectCX = "Project CX";
    QString m_APIKey = "API Key";
    QSettings m_settings = {"Google Plugin",QSettings::IniFormat};
};

#endif // GoogleSETTINGS_H
