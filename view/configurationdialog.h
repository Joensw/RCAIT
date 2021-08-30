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
 * @brief The ConfigurationDialog class is used to insure programm critical paths are set before continuing on startup
 */
class ConfigurationDialog : public QDialog
{
    Q_OBJECT

public:
    explicit ConfigurationDialog(QWidget *parent = nullptr);
    ~ConfigurationDialog();

    /**
     * @brief closeEvent closes the dialog on a close event, if it has accepted the input, shows a quit UI otherwise
     * @param event close event
     */
    virtual void closeEvent(QCloseEvent *event) override;

    /**
     * @brief reject a reject event is treated as a close call
     */
    virtual void reject() override;

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
     * @param classificationPluginsDir the specifed classification plugin directory
     * @param imageLoaderPluginsDir the specifed image loader plugin directory
     */
    void sig_directoriesSpecified(QString projectsDir, QString classificationPluginsDir, QString imageLoaderPluginsDir);

private:
    Ui::ConfigurationDialog *ui;

    QString mProjectDir;
    QString mClassificationPluginsDir;
    QString mImageLoaderPluginsDir;

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
};

#endif // CONFIGURATIONDIALOG_H
