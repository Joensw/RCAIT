#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
#include <QtCharts/QChartView>
#include <QtCharts/QLineSeries>
#include <QtWidgets/QApplication>
#include <QtWidgets/QMainWindow>
#include <QtWidgets/QComboBox>
#include <QTranslator>
#include <QPushButton>
#include <QDir>

#include "aitrainingwidget.h"
#include "inputimageswidget.h"
#include "startwidget.h"

QT_BEGIN_NAMESPACE
namespace Ui { class MainWindow; }
QT_END_NAMESPACE

class MainWindow : public QMainWindow
{
    Q_OBJECT

protected:
    // this event is called, when a new translator is loaded or the system language is changed
    void changeEvent(QEvent*);

public:
    explicit MainWindow(QWidget *parent = nullptr);
    ~MainWindow();
    void addProjects(QStringList projects);

    StartWidget * getStartWidget();
    InputImagesWidget *getInputImagesWidget();
    AITrainingWidget *getAITrainingWidget();

signals:
    void sig_openSettings();

private slots:
    void slot_settingsButton_clicked();

private:
    Ui::MainWindow *ui;
    QTranslator m_translator; /*< contains the translations for this application*/
    QString m_currLang; /*< contains the currently loaded language*/
    const QString m_langPath = QDir(":/i18n/").exists()? ":/i18n/" : QDir::currentPath() + "/"; /*< Path of language files. This is always fixed.*/
    QPushButton * pushButton_settings = new QPushButton();

    void placeSettingsButton();

};
#endif // MAINWINDOW_H
