#ifndef MMCLASSIFICATIONSETTINGS_H
#define MMCLASSIFICATIONSETTINGS_H

#include <QWidget>
#include <QSettings>
#include <QtCore>

namespace Ui {
class MMClassificationSettings;
}

class MMClassificationSettings : public QWidget
{
    Q_OBJECT

public:
    explicit MMClassificationSettings(QWidget *parent = nullptr);
    ~MMClassificationSettings();
    void saveSettings();
    void loadSettings();
    QString getMMClassificationPath();
    QString getMMClsPath();
    QString getPythonPath();


    QSettings m_settings = {"MMClassification Plugin", QSettings::IniFormat};

private:
    Ui::MMClassificationSettings *ui;
    QString m_mmclassificationPath = "mmclassification path";
    QString m_mmclsPath = "mmcls path";
    QString m_pythonPath = "Python Path";

};

#endif // MMCLASSIFICATIONSETTINGS_H
