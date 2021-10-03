#ifndef NEWPROJECTDIALOG_H
#define NEWPROJECTDIALOG_H

#include <QDialog>


namespace Ui {
class NewProjectDialog;
}
/**
 * @brief The NewProjectDialog class is a UI class that is for specifying the details of a new project
 */
class NewProjectDialog : public QDialog
{
    Q_OBJECT

public:
    /**
     * @brief NewProjectDialog creates a newProjectDialog
     * @param parent optional parent argument
     */
    explicit NewProjectDialog(QWidget *parent = nullptr);

    /**
     * @brief destructor
     */
    ~NewProjectDialog();

    /**
     * @brief setErrorMessage sets the displayed error message in the UI
     * @param error the error message to be shown in the UI
     */
    void setErrorMessage(const QString &error);

    /**
     * @brief showErrorMessage show the label that houses the error message
     */
    void showErrorMessage();

    /**
     * @brief hideErrorMessage hide the label that houses the error message
     */
    void hideErrorMessage();

signals:
    /**
     * @brief sig_newProjectConfirm emitted when a project with the specified parameters is to be created
     * @param projectName name of the new project
     */
    void sig_newProjectConfirm(QString projectName);
private:
    Ui::NewProjectDialog *ui;

private slots:
    //slots correspond with the identically named button in the UI
    [[maybe_unused]] void on_buttonBox_accepted();
    [[maybe_unused]] void on_buttonBox_rejected();


};

#endif // NEWPROJECTDIALOG_H
