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





private:
    Ui::BingSettings *ui;
    QString m_pythonPath = "Python Path";
    QSettings m_settings = {"Bing Plugin",QSettings::IniFormat};
};

#endif // BINGSETTINGS_H
