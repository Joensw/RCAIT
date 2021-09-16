#ifndef REMOVEMODELDIALOG_H
#define REMOVEMODELDIALOG_H

#include <QDialog>

namespace Ui {
class RemoveModelDialog;
}

/**
 * @brief The RemoveModelDialog class is UI class to confirm the removal of a model
 */
class RemoveModelDialog : public QDialog
{
    Q_OBJECT

public:
    /**
     * @brief RemoveModelDialog creates a RemoveModelDialog
     * @param parent optional parent argument
     * @param toRemove name of the model to be removed
     */
    explicit RemoveModelDialog(QWidget *parent = nullptr, QString toRemove = "");
    ~RemoveModelDialog();

    /**
     * @return the name of the model that is to be removed
     */
    QString getModelName();

signals:
    /**
     * @brief sig_removeModelConfirm emitted when the model removal is confirmed
     */
    void sig_removeModelConfirm();


private:
    static constexpr auto MODEL_NAME_PLACEHOLDER = "&lt;name&gt;";

    Ui::RemoveModelDialog *ui;



    QString mToRemove;
private slots:
    //slots correspond with the identically named button in the UI
    [[maybe_unused]] void on_buttonBox_accepted();
    [[maybe_unused]] void on_buttonBox_rejected();
};

#endif // REMOVEMODELDIALOG_H
