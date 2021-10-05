#ifndef REMOVEPROJECTDIALOG_H
#define REMOVEPROJECTDIALOG_H

#include <QDialog>
#include <animationutilities.h>

namespace Ui {
class RemoveProjectDialog;
}

/**
 * @brief The RemoveProjectDialog class is a UI class to confirm the removal of a project
 */
class RemoveProjectDialog : public QDialog
{
    Q_OBJECT

public:
    /**
     * @brief RemoveProjectDialog creates a removeProjectDialog
     * @param parent optional parent argument
     * @param toRemove name of the project that is to be removed
     */
    explicit RemoveProjectDialog(QWidget *parent = nullptr, QString toRemove = "");

    /**
     * @brief destructor
     */

    ~RemoveProjectDialog();

    /**
     * @return the name of the project that is to be removed
     */
    QString getProjectName();

    /**
     * @brief setErrorMessage sets the displayed error message in the UI
     * @param error the error message to be shown in the UI
     */
    void setErrorMessage(const QString &error);
signals:

    /**
     * @brief sig_removeProjectConfirm emitted when the projects removal is confirmed
     */
    void sig_removeProjectConfirm();

private:
    static constexpr auto PROJECT_NAME_PLACEHOLDER = "&lt;name&gt;";

    Ui::RemoveProjectDialog *ui;



    QString mToRemove;

private slots:
    //slots correspond with the identically named button in the UI
    [[maybe_unused]] void on_buttonBox_accepted();
    [[maybe_unused]] void on_buttonBox_rejected();
};

#endif // REMOVEPROJECTDIALOG_H
