#ifndef CONFIGURATIONDIALOG_H
#define CONFIGURATIONDIALOG_H

#include <QDialog>
#include <QFileDialog>
#include <QMessageBox>
#include <QCloseEvent>


namespace Ui {
class ConfigurationDialog;
}

class ConfigurationDialog : public QDialog
{
    Q_OBJECT

public:
    explicit ConfigurationDialog(QWidget *parent = nullptr);
    ~ConfigurationDialog();
    virtual void closeEvent(QCloseEvent *event) override;
    virtual void reject() override;

    void setError(QString error);
    void confirm();

signals:
    void sig_directoriesSpecified(QString projectsDir, QString classificationPluginsDir, QString imageLoaderPluginsDir);
    void sig_forceClose();
private:
    Ui::ConfigurationDialog *ui;

    QString mProjectDir;
    QString mClassificationPluginsDir;
    QString mImageLoaderPluginsDir;

    bool mIsCloseable;
private slots:
    void on_pushButton_apply_clicked();

    void slot_setProjectDir();
    void slot_setClassificationPluginsDir();
    void slot_setImageLoaderPluginsDir();
};

#endif // CONFIGURATIONDIALOG_H
