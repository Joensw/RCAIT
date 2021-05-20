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
    explicit RemoveModelDialog(QWidget *parent = nullptr);
    ~RemoveModelDialog();

private:
    Ui::RemoveModelDialog *ui;
};

#endif // REMOVEMODELDIALOG_H
