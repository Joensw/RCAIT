#ifndef REMOVEMODELDIALOG_H
#define REMOVEMODELDIALOG_H

#include <QDialog>

namespace Ui {
class RemoveModelDialog;
}

class RemoveModelDialog : public QDialog
{
    Q_OBJECT

public:
    explicit RemoveModelDialog(QWidget *parent = nullptr, QString toRemove = "");
    ~RemoveModelDialog();

    QString getModelName();

signals:
    void sig_removeModelConfirm();


private:
    Ui::RemoveModelDialog *ui;

    QString mToRemove;
private slots:
    void on_buttonBox_accepted();
    void on_buttonBox_rejected();
};

#endif // REMOVEMODELDIALOG_H
