#ifndef REMOVEPROJECTDIALOG_H
#define REMOVEPROJECTDIALOG_H

#include <QDialog>

namespace Ui {
class RemoveProjectDialog;
}

class RemoveProjectDialog : public QDialog
{
    Q_OBJECT

public:
    explicit RemoveProjectDialog(QWidget *parent = nullptr, QString toRemove = "");
    ~RemoveProjectDialog();
    QString getProjectName();

signals:
    void sig_removeProjectConfirm();

private:
    Ui::RemoveProjectDialog *ui;

    QString mToRemove;

private slots:
    void on_buttonBox_accepted();
    void on_buttonBox_rejected();
};

#endif // REMOVEPROJECTDIALOG_H
