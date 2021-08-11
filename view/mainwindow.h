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
#include "imageinspectionwidget.h"
#include "customtabwidget.h"

QT_BEGIN_NAMESPACE
namespace Ui { class MainWindow; }
QT_END_NAMESPACE

/**
 * @brief The MainWindow class is the primary UI for the application and houses all critical features.
 */
class MainWindow : public QMainWindow
{
    Q_OBJECT

protected:
    // this event is called, when a new translator is loaded or the system language is changed
    void changeEvent(QEvent*) override;

public:
    /**
     * @brief MainWindow creates a new MainWindow
     * @param parent
     */
    explicit MainWindow(QWidget *parent = nullptr);
    ~MainWindow();

    StartWidget * getStartWidget();
    ImportFilesWidget * getImportFilesWidget();
    AITrainingWidget *getAITrainingWidget();
    InputImagesWidget *getInputImagesWidget();
    ResultsWidget *getResultsWidget();
    AutomationWidget *getAutomationWidget();
    ImageInspectionWidget* getImageInspectionWidget();
    CustomTabWidget* getTabWidget();

signals:
    /**
     * @brief sig_openSettings emitted when the settings UI is to be opened
     */
    void sig_openSettings();

private slots:
    //slots correspond with the identically named button in the UI
    void slot_settingsButton_clicked();

private:
    Ui::MainWindow *ui;
    QPushButton * pushButton_settings = new QPushButton(this);

    void placeSettingsButton();
};
#endif // MAINWINDOW_H
