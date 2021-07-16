#ifndef NEWMODELDIALOG_H
#define NEWMODELDIALOG_H

#include <QDialog>

namespace Ui {
class NewModelDialog;
}

class NewModelDialog : public QDialog
{
    Q_OBJECT

public:
    explicit NewModelDialog(QWidget *parent = nullptr, QStringList classificationPlugins = QStringList());
    ~NewModelDialog();
    void setAvailableBases(QStringList bases);
public slots:
    void slot_classifactionPlugin_currentTextChanged(QString text);

signals:
    void sig_newModelConfirm(QString modelName, QString pluginName, QString baseModel);
    void sig_pluginSelected(QString pluginName);
private:
    Ui::NewModelDialog *ui;
private slots:
    void on_buttonBox_accepted();
    void on_buttonBox_rejected();

};

#endif // NEWMODELDIALOG_H
