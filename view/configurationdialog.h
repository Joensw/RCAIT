#ifndef CONFIGURATIONDIALOG_H
#define CONFIGURATIONDIALOG_H

#include <QDialog>
#include <QFileDialog>
#include <QMessageBox>
#include <QCloseEvent>


namespace Ui {
class ConfigurationDialog;
}

/**
 * The configuration UI will appear on first time application use and will also appear subsequently if the set paths are not resolvable anymore
 * such as when the underlying folders are deleted
 * @brief The ConfigurationDialog class is used to insure program critical paths are set before continuing on startup
 */
class ConfigurationDialog : public QDialog
{
    Q_OBJECT

public:

    /**
     * @brief ConfigurationDialog creates a new ConfigurationDialog
     * @param parent optional parent argument
     */
    explicit ConfigurationDialog(QWidget *parent = nullptr);

    /**
     * @brief destructor
     */

    ~ConfigurationDialog() override;

    /**
     * @brief closeEvent closes the dialog on a close event, if it has accepted the input, shows a quit UI otherwise
     * @param event close event
     */
    void closeEvent(QCloseEvent *event) override;

    /**
     * @brief reject a reject event is treated as a close call
     */
    void reject() override;

    /**
     * @brief showError lets the standardized error message in the configuration UI appear
     */
    void showError();

    /**
     * @brief confirm prompts the configuration UI to be closed
     */
    void confirm();

signals:

    /**
     * Ports the new paths into the application if they are acceptable, shows an error message in the UI otherwise
     * @brief sig_directoriesSpecified emitted when the input paths are to be checked for validity
     * @param projectsDir the specified projects directory
     * @param classificationPluginsDir the specified classification plugin directory
     * @param imageLoaderPluginsDir the specified image loader plugin directory
     */
    void sig_directoriesSpecified(QString projectsDir, QString classificationPluginsDir, QString imageLoaderPluginsDir, QString pythonPath);

private:
    static constexpr auto QUIT_DIALOG_TITLE = QT_TR_NOOP("Quit confirmation");
    static constexpr auto QUIT_MSG = QT_TR_NOOP("Are you sure you want to quit?\n The application will terminate");
    static constexpr auto MISSING_PATHS_MSG = QT_TR_NOOP("Please specifiy all paths uniquely before proceeding.");

    static constexpr auto PROJECT_SELECT_MSG = QT_TR_NOOP("Select project directory");
    static constexpr auto CLASSIFICATION_SELECT_MSG = QT_TR_NOOP("Select classification plugin directory");
    static constexpr auto LOADER_SELECT_MSG = QT_TR_NOOP("Select image loader plugin directory");
    static constexpr auto PYTHON_SELECT_MSG = QT_TR_NOOP("Select Python path");

    Ui::ConfigurationDialog *ui;

    QString mProjectDir;
    QString mClassificationPluginsDir;
    QString mImageLoaderPluginsDir;
    QString mPythonPath;

    bool mIsCloseable;
private slots:
    /**
     * @brief on_pushButton_apply_clicked emits the {sig_directories} signal when the "OK" button in the UI is pressed
     */
    [[maybe_unused]] void on_pushButton_apply_clicked();

    /**
     * @brief slot_setProjectDir shows the user selected projects directory path from a file dialog in the UI
     */
    [[maybe_unused]] void slot_setProjectDir();

    /**
     * @brief slot_setClassificationPluginsDir shows the user selected classification plugin directory path from a file dialog in the UI
     */
    [[maybe_unused]] void slot_setClassificationPluginsDir();

    /**
     * @brief slot_setImageLoaderPluginsDir shows the user selected image loader plugin directory path from a file dialog in the UI
     */
    [[maybe_unused]] void slot_setImageLoaderPluginsDir();

    /**
     * @brief slot_setPythonPath shows the user selected python path from a file dialog in the ui
     */
    void slot_setPythonPath();
};

#endif // CONFIGURATIONDIALOG_H
