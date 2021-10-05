#ifndef MMCLASSIFICATIONSETTINGS_H
#define MMCLASSIFICATIONSETTINGS_H

#include <QWidget>
#include <QSettings>
#include <QtCore>

namespace Ui {
class MMClassificationSettings;
}

/**
 * @brief The MMClassificationSettings class manages the settings of the MMClassificationPlugin
 */
class MMClassificationSettings : public QWidget
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
     * @brief MMClassificationSettings creates a new instance of this class
     * @param parent the parent widget of this widget
     */
    explicit MMClassificationSettings(QWidget *parent = nullptr);

    /**
     * @brief destructor
     */

    ~MMClassificationSettings();

    /**
     * @brief saveSettings saves the settings made in the configuration widget
     */
    void saveSettings();

    /**
     * @brief loadSettings loads the saved settings
     */
    void loadSettings();

    /**
     * @brief getMMClassificationPath returns the saved path to the mmclassification directory,
     *        where configs and imagenet checkpoint files are located
     * @return the previously saved path to the mmclassification directory, an empty QString otherwise
     */
    QString getMMClassificationPath();

    /**
     * @brief getPythonPath returns the saved path to the directory, where python is located
     * @return the previously saved python path, an empty QString otherwise
     */
    QString getPythonPath();

private:
    Ui::MMClassificationSettings *ui;

    QSettings m_settings = {"MMClassification Plugin", QSettings::IniFormat};

    QString m_mmclassificationPath = "mmclassification path";
    QString m_pythonPath = "Python Path";

};

#endif // MMCLASSIFICATIONSETTINGS_H
