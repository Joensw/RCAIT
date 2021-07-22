#ifndef GLOBALSETTINGSWIDGET_H
#define GLOBALSETTINGSWIDGET_H

#include <QWidget>
#include <QString>

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
    ~GlobalSettingsWidget();

    /**
     * @brief setNewProjectPath sets the path to the directory where the applications manages its projects
     * @param path the absolute new path to use
     */
    void setNewProjectPath(QString path);

    /**
     * @brief setNewClassificationPluginPath set the path to the directory where the application looks for the external classification plugins
     * @param path the new absolute path to use
     */
    void setNewClassificationPluginPath(QString path);

    /**
     * @brief setNewImageLoaderPath set the path to the directory where the application looks for the external image loader plugins
     * @param path the new absolute path to use
     */
    void setNewImageLoaderPath(QString path);

    /**
     * Called when temporary paths have been accepeted or denied
     * @brief clearNewPaths clear the new paths shown in the UI
     */
    void clearNewPaths();

    /**
     * @brief showUpdate displays an update message in the UI about the amount of paths changed
     * @param integer argument representing the paths sucessfully applied
     */
    void showUpdate(int amount);

    /**
     * @brief showNonUpdate displays a message in the UI, signifying that no changes have occured
     */
    void showNonUpdate();

    /**
     * @brief setError sets an Error message to be shown in the UI
     * @param error the error message to be shown
     */
    void setError(QString error);

    /**
     * @brief setCurrentProjectsDir set the current projects directory shown in the UI
     * @param path path to be shown
     */
    void setCurrentProjectsDir(QString path);

    /**
     * @brief setCurrentClassificationDir set the current classification plugin directory shown in the UI
     * @param path path to be shown
     */
    void setCurrentClassificationDir(QString path);

    /**
     * @brief setCurrentImageLoaderDir set the current classification plugin directory shown in the UI
     * @param path path to be shown
     */
    void setCurrentImageLoaderDir(QString path);
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
     * @brief sig_wasTranslated emitted when a translation of the current objet has taken place
     */
    void sig_wasTranslated();
protected:
    void changeEvent(QEvent *event);
private slots:
    //slots correspond with the identically named button in the UI
    void on_pushButton_project_clicked();
    void on_pushButton_classification_clicked();
    void on_pushButton_imageLoader_clicked();
private:
    Ui::GlobalSettingsWidget *ui;
};

#endif // GLOBALSETTINGSWIDGET_H
