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
#include <resultswidget.h>

#include "aitrainingwidget.h"
#include "automationwidget.h"
#include "inputimageswidget.h"
#include "startwidget.h"
#include "importfileswidget.h"
#include "imagesection.h"

QT_BEGIN_NAMESPACE
namespace Ui { class MainWindow; }
QT_END_NAMESPACE

class MainWindow : public QMainWindow
{
    Q_OBJECT

protected:
    // this event is called, when a new translator is loaded or the system language is changed
    void changeEvent(QEvent*) override;

public:
    explicit MainWindow(QWidget *parent = nullptr);
    ~MainWindow();

    StartWidget * getStartWidget();
    ImportFilesWidget * getImportFilesWidget();
    AITrainingWidget *getAITrainingWidget();
    InputImagesWidget *getInputImagesWidget();
    ResultsWidget *getResultsWidget();
    AutomationWidget *getAutomationWidget();
    ImageSection* getImageSectionWidget();

signals:
    void sig_openSettings();

private slots:
    void slot_settingsButton_clicked();

    void on_pushButton_openProject_clicked();

private:
    Ui::MainWindow *ui;
    QPushButton * pushButton_settings = new QPushButton(this);

    void placeSettingsButton();
};
#endif // MAINWINDOW_H
