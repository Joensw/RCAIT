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

#include <aitrainingwidget.h>
#include <automationwidget.h>
#include <inputimageswidget.h>
#include <startwidget.h>
#include <importfileswidget.h>
#include <imageinspectionwidget.h>
#include <customtabwidget.h>

QT_BEGIN_NAMESPACE
namespace Ui { class MainWindow; }
QT_END_NAMESPACE

/**
 * @brief The MainWindow class is the primary UI for the application and houses all critical features.
 */
class MainWindow : public QMainWindow {
Q_OBJECT

protected:
    /**
     * @brief changeEvent this event is called, when a new translator is loaded or the system language is changed
     */
    void changeEvent(QEvent *) override;

public:
    /**
     * @brief MainWindow creates a new MainWindow
     * @param parent
     */
    explicit MainWindow(QWidget *parent = nullptr);

    /**
     * @brief destructor
     */

    ~MainWindow() override;

    /**
    * @return returns the start widget
    */

   [[nodiscard]] StartWidget *getStartWidget();

    /**
    * @return  returns the import files widget
    */

   [[nodiscard]] ImportFilesWidget *getImportFilesWidget();

    /**
    * @return returns the AI training widget
    */

   [[nodiscard]] AITrainingWidget *getAITrainingWidget();

    /**
    * @return returns the input images widget
    */

   [[nodiscard]] InputImagesWidget *getInputImagesWidget();

    /**
    * @return returns the results widget
    */

   [[nodiscard]] ResultsWidget *getResultsWidget();

    /**
    * @return returns the automation widget
    */

   [[nodiscard]] AutomationWidget *getAutomationWidget();

    /**
    * @return return the image inspection widget
    */

   [[nodiscard]] ImageInspectionWidget *getImageInspectionWidget();

    /**
    * @return returns the tab widget
    */

   [[nodiscard]] CustomTabWidget *getTabWidget();

signals:

    /**
     * @brief sig_openSettings emitted when the settings UI is to be opened
     */
    void sig_openSettings();

    /**
     * @brief sig_changedWindowState changes the window state to the specific state
     * @param flags the wanted state of the window
     */

    void sig_changedWindowState(Qt::WindowStates flags);

public slots:

    /**
     * @brief slot_normalizeWindow called when the mainwindow should be normal, i.e. neither maximized, minimized, nor fullscreen
     */

    void slot_normalizeWindow();

    /**
     * @brief slot_maximizeWindow called when the mainwindow  should fill the screen
     */

    void slot_maximizeWindow();

private slots:

    //slots correspond with the identically named button in the UI
    void slot_settingsButton_clicked();

private:
    static constexpr int EDGE = 2;
    static constexpr int SETTINGSBUTTON_WIDTH = 32;
    static constexpr int SETTINGSBUTTON_HEIGHT = 57;
    static constexpr auto SETTINGSBUTTON_ICON = ":/TabIcons/Filled/Tab_Settings_Icon.svg";

    Ui::MainWindow *ui;
    QPushButton *m_pushButton_settings;

    void placeSettingsButton();
};
#endif // MAINWINDOW_H
