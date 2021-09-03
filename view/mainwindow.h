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
#include <ce_string.h>

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
class MainWindow : public QMainWindow {
Q_OBJECT

protected:
    // this event is called, when a new translator is loaded or the system language is changed
    void changeEvent(QEvent *) override;

public:
    /**
     * @brief MainWindow creates a new MainWindow
     * @param parent
     */
    explicit MainWindow(QWidget *parent = nullptr);

    ~MainWindow();

   [[nodiscard]] StartWidget *getStartWidget();

   [[nodiscard]] ImportFilesWidget *getImportFilesWidget();

   [[nodiscard]] AITrainingWidget *getAITrainingWidget();

   [[nodiscard]] InputImagesWidget *getInputImagesWidget();

   [[nodiscard]] ResultsWidget *getResultsWidget();

   [[nodiscard]] AutomationWidget *getAutomationWidget();

   [[nodiscard]] ImageInspectionWidget *getImageInspectionWidget();

   [[nodiscard]] CustomTabWidget *getTabWidget();

signals:

    /**
     * @brief sig_openSettings emitted when the settings UI is to be opened
     */
    void sig_openSettings();

    void sig_changedWindowState(Qt::WindowStates flags);

public slots:

    void slot_normalizeWindow();

    void slot_maximizeWindow();

private slots:

    //slots correspond with the identically named button in the UI
    void slot_settingsButton_clicked();

private:
    constexpr int EDGE = 2;
    constexpr int SETTINGSBUTTON_WIDTH = 32;
    constexpr int SETTINGSBUTTON_HEIGHT = 57;
    constexpr CE_String SETTINGSBUTTON_ICON = ":/Resources/TabIcons/Filled/Tab_Settings_Icon.svg";

    Ui::MainWindow *ui;
    QPushButton *m_pushButton_settings;

    void placeSettingsButton();
};
#endif // MAINWINDOW_H
