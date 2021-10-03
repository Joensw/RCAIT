#ifndef STARTWIDGET_H
#define STARTWIDGET_H

#include <QWidget>
#include <QtWidgets/QComboBox>
#include <QTranslator>
#include <QDir>
#include "newprojectdialog.h"

namespace Ui {
class StartWidget;
}

/**
 * @brief The StartWidget class is a UI class for creating, deleting and opening projects. Additionally the language can be changed from here.
 */
class StartWidget : public QWidget
{
    Q_OBJECT

public:
    /**
     * @brief StartWidget creates a StartWidget
     * @param parent optional parent arugment
     */
    explicit StartWidget(QWidget *parent = nullptr);

    /**
     * @brief destructor
     */
    ~StartWidget();

    /**
     * @return the language currently selected in the language combobox
     */
    QString getLanguageEntry();

    /**
     * @brief addProjects add a list of projects to the shown projects in the UI
     * @param projects list of projects names to be added
     */
    void addProjects(QStringList projects);

    /**
     * @brief addProject add a single project to the shown project in the UI
     * @param project name of the project
     */
    void addProject(QString project);

    /**
     * @brief clearProjectList empty the list of shown projects
     */
    void clearProjectList();

    /**
     * @brief setLoadButtonEnabled disables or enables the state of the project action bar (remove, open)
     * @param state true to enabled, false to disable
     */
    void setActionButtonsEnabled(bool state);

    /**
     * @brief resetListSelection resets the project list so that no item is currently selected
     */
    void resetListSelection();

public slots:

    /**
     * @brief slot_changedWindowState called when the window state has change, sets the ui to reflect this
     * @param flags the new state the window has
     */
    void slot_changedWindowState(Qt::WindowStates flags);

    /**
     * @brief slot_imagesUpdated called when an image loading process has finished
     */
    void slot_imagesUpdated();

    /**
     * @brief slot_startLoading called when an image loading process is started to prevent the selection of a new project
     */
    void slot_startLoading();


private:
    Ui::StartWidget *ui;

    QTranslator m_translator; /*< contains the translations for this application*/
    QString m_currLang; /*< contains the currently loaded language*/
    const QString m_langPath = QDir(":/i18n/").exists()? ":/i18n/" : QDir::currentPath() + "/"; /*< Path of language files. This is always fixed.*/
    static auto constexpr QLISTWIDGET_UNSELECT_INDEX = -1;

    //see https://wiki.qt.io/How_to_create_a_multi_language_application
    void populateLanguageMenu(QComboBox *box);
    void loadLanguage(const QString& rLanguage);
    void switchTranslator(QTranslator& translator, const QString& filename);

private slots:
    //slots correspond with the identically named button in the UI
    [[maybe_unused]] void on_pushButton_newProject_clicked();
    [[maybe_unused]] void on_pushButton_removeProject_clicked();
    [[maybe_unused]] void on_pushButton_openProject_clicked();
    [[maybe_unused]] void on_comboBox_languageSelection_currentTextChanged(const QString &arg1);
    [[maybe_unused]] void on_pushButton_toggleFullscreen_toggled(bool checked);

    void slot_setEnableActionButtons();

signals:
    /**
     * @brief sig_newProject emitted when the button in the UI to create a new project is pressed
     */
    void sig_newProject();

    /**
     * @brief sig_removeProject emitted when the button in the UI to remove a project is pressed
     * @param projectName name of the project to be deleted
     */
    void sig_removeProject(QString projectName);

    /**
     * @brief sig_openProject emitted when the button in the UI to open a project is pressed
     * @param projectName name of the project to be opened
     */
    void sig_openProject(QString projectName);

    /**
     * @brief This signal is emitted when the main window has been maximized.
     * It is used for a button to control the size of the main window.
     */
    void sig_maximizeWindow();

    /**
     * @brief This signal is emitted when the main window has been normalized.
     * It is used for a button to control the size of the main window.
     */
    void sig_normalizeWindow();
};

#endif // STARTWIDGET_H
