#ifndef NEWPROJECTDIALOG_H
#define NEWPROJECTDIALOG_H

#include <QDialog>

namespace Ui {
class NewProjectDialog;
}

class NewProjectDialog : public QDialog
{
    Q_OBJECT

public:
    explicit NewProjectDialog(QWidget *parent = nullptr);
    ~NewProjectDialog();

    void setErrorMessage(QString error);
    void showErrorMessage();
    void hideErrorMessage();

signals:
    void sig_newProjectConfirm(QString projectName);
private:
    Ui::NewProjectDialog *ui;

private slots:
    void on_buttonBox_accepted();
    void on_buttonBox_rejected();


};

#endif // NEWPROJECTDIALOG_H
