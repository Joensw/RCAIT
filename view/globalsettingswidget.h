#ifndef GLOBALSETTINGSWIDGET_H
#define GLOBALSETTINGSWIDGET_H

#include <QWidget>
#include <QString>
#include <QLabel>
#include <QResizeEvent>

namespace Ui {
class GlobalSettingsWidget;
}
/**
 * @brief The GlobalSettingsWidget class is a UI class that houses the global settings for the application
 */
class GlobalSettingsWidget : public QWidget
{
    Q_OBJECT

public:
    /**
     * @brief GlobalSettingsWidget creates a new GlobalSettingsWidget
     * @param parent
     */
    explicit GlobalSettingsWidget(QWidget *parent = nullptr);

    /**
     * @brief destructor
     */
    ~GlobalSettingsWidget() override;

    /**
     * @brief setNewProjectPath sets the path to the directory where the applications manages its projects
     * @param path the absolute new path to use
     */
    void setNewProjectPath(const QString& path);

    /**
     * @brief setNewClassificationPluginPath set the path to the directory where the application looks for the external classification plugins
     * @param path the new absolute path to use
     */
    void setNewClassificationPluginPath(const QString& path);

    /**
     * @brief setNewImageLoaderPath set the path to the directory where the application looks for the external image loader plugins
     * @param path the new absolute path to use
     */
    void setNewImageLoaderPath(const QString& path);

    /**
     * @brief setNewPythonPath set the path to the python executable to used in general
     * @param path the new absolute path to use
     */
    void setNewPythonPath(const QString& path);

    /**
     * Called when temporary paths have been accepted or denied
     * @brief clearNewPaths clear the new paths shown in the UI
     */
    void clearNewPaths();

    /**
     * @brief showUpdate displays an update message in the UI about the amount of paths changed
     * @param integer argument representing the paths successfully applied
     */
    void showUpdate(int amount);

    /**
     * @brief setError sets an Error message to be shown in the UI
     * @param error the error message to be shown
     */
    void setError(const QString& error);

    /**
     * @brief setCurrentProjectsDir set the current projects directory shown in the UI
     * @param path path to be shown
     */
    void setCurrentProjectsDir(const QString& path);

    /**
     * @brief setCurrentClassificationDir set the current classification plugin directory shown in the UI
     * @param path path to be shown
     */
    void setCurrentClassificationDir(const QString& path);

    /**
     * @brief setCurrentImageLoaderDir set the current classification plugin directory shown in the UI
     * @param path path to be shown
     */
    void setCurrentImageLoaderDir(const QString& path);

    /**
     * @brief setCurrentPythonPath set the current path to the python executable
     * @param path path to be shown
     */
    void setCurrentPythonPath(const QString& path);

signals:
    /**
     * @brief sig_setProjectDir emitted when a file dialog is to be opened to choose a new projects directory
     */
    void sig_setProjectDir();

    /**
     * @brief sig_setClassificationPluginsDir emitted when a file dialog is to be opened to choose a new classification plugin directory
     */
    void sig_setClassificationPluginsDir();

    /**
     * @brief sig_setImageLoaderPluginsDir emitted when a file dialog is to be opened to choose a new image loader plugin directory
     */
    void sig_setImageLoaderPluginsDir();

    /**
     * @brief sig_setGeneralPythonPath emitted when a file dialog is to be opened to choose a new path to the python executable
     */
    void sig_setGeneralPythonPath();

protected:

    /**
     * @brief changeEvent event handler
     *
     * @param event incoming event
     */
    void changeEvent(QEvent *event) override;

private slots:

    //slots correspond with the identically named button in the UI
    [[maybe_unused]] void on_pushButton_project_clicked();

    [[maybe_unused]] void on_pushButton_classification_clicked();

    [[maybe_unused]] void on_pushButton_imageLoader_clicked();

    [[maybe_unused]] void on_pushButton_python_clicked();

private:

    void setText(const QString &path, QLabel* label);

    static constexpr auto STYLESHEET_RED = "QLabel { color : red; }";
    static constexpr auto STYLESHEET_GREEN = "QLabel { color : green; }";
    static constexpr auto STYLESHEET_BLUE = "QLabel { color : blue; }";

    static constexpr auto SUCCESS_UPDATED_PATHS_MSG = QT_TR_NOOP("Updated %1 path(s) successfully");
    static constexpr auto NO_CHANGES_MSG = QT_TR_NOOP("No changes were made");

    Ui::GlobalSettingsWidget *ui;
};

#endif // GLOBALSETTINGSWIDGET_H
