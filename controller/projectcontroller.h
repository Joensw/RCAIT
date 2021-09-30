/**
 * @file projectcontroller.h
 *
 * @brief connects the logic of the project management with the user interface
 *
 * @author Jonas Wille
 */
#ifndef PROJECTCONTROLLER_H
#define PROJECTCONTROLLER_H

#include <QString>
#include <QDir>
#include <newprojectdialog.h>
#include <removeprojectdialog.h>
#include <startwidget.h>
#include <datamanager.h>
#include <utility>

/**
 * @brief The ProjectController class mediates between the project logic and project UI
 *
 */
class ProjectController final : public QObject
{
    Q_OBJECT
public:

    /**
     * @brief ProjectController constructs a project controller
     * @param parent optional parent argument
     * @param dataManager datamanager argument
     * @param startWidget widget to be controlled and updated
     */
    explicit ProjectController(QObject *parent = nullptr, DataManager *dataManager = nullptr, StartWidget *startWidget = nullptr);

    /**
     * @brief operator = deleted assignment operator
     */
    ProjectController &operator=(const ProjectController &) = delete;

    /**
     * @brief refresh clears the project list in the UI and reloads the current projects
     */
    void refresh();

signals:

    /**
     * @brief sig_projectPathUpdated emitted when a project is opened
     */

    void sig_projectPathUpdated();

public slots:
    /**
     * @brief slot_newProject opens the UI to create a new project
     */
    void slot_newProject();

    /**
     * @brief slot_newProjectConfirm creates a new project, iff the name is considered valid
     * @param projectName name of the new project
     */
    void slot_newProjectConfirm(QString projectName);

    /**
     * @brief slot_removeProject open the confirmation UI to delete a project
     * @param projectName the name of the project
     */
    void slot_removeProject(QString projectName);

    /**
     * @brief slot_removeProjectConfirm deletes the project previously specified
     */
    void slot_removeProjectConfirm();

    /**
     * @brief slot_openProject loads a project that is to be used into the application,
     * @param projectName name of the project
     */
    void slot_openProject(QString projectName);

    /**
     * @brief slot_projectDirectoryChanged refreshes the project UI
     */
    void slot_projectDirectoryChanged();

private:
    DataManager *mDataManager;
    NewProjectDialog *mNewProjectDialog{};
    RemoveProjectDialog *mRemoveProjectDialog{};
    StartWidget *mStartWidget;

    static auto constexpr OPEN_PROJECT_ERROR = QT_TR_NOOP("Cannot remove the currently opened project!");

};

#endif // PROJECTCONTROLLER_H
