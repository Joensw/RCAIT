#ifndef REMOVEPROJECTDIALOG_H
#define REMOVEPROJECTDIALOG_H

#include <QDialog>

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
    ~RemoveProjectDialog();

    /**
     * @return the name of the project that is to be removed
     */
    QString getProjectName();

signals:

    /**
     * @brief sig_removeProjectConfirm emitted when the projects removal is confirmed
     */
    void sig_removeProjectConfirm();

private:
    Ui::RemoveProjectDialog *ui;

    QString mToRemove;

private slots:
    //slots correspond with the identically named button in the UI
    void on_buttonBox_accepted();
    void on_buttonBox_rejected();
};

#endif // REMOVEPROJECTDIALOG_H
