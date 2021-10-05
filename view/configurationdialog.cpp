#include "configurationdialog.h"
#include "ui_configurationdialog.h"

ConfigurationDialog::ConfigurationDialog(QWidget *parent) :
    QDialog(parent),
    ui(new Ui::ConfigurationDialog)
{
    ui->setupUi(this);
    connect(ui->pushButton_projectDir, &QPushButton::clicked, this, &ConfigurationDialog::slot_setProjectDir);
    connect(ui->pushButton_classificationDir, &QPushButton::clicked, this, &ConfigurationDialog::slot_setClassificationPluginsDir);
    connect(ui->pushButton_imageLoaderDir, &QPushButton::clicked, this, &ConfigurationDialog::slot_setImageLoaderPluginsDir);
    connect(ui->pushButton_pythonPath, &QPushButton::clicked, this, &ConfigurationDialog::slot_setPythonPath);

    ui->label_error->hide();
    mIsCloseable = false;
}

ConfigurationDialog::~ConfigurationDialog()
{
    delete ui;
}

void ConfigurationDialog::closeEvent(QCloseEvent *event)
{
    if(mIsCloseable){
        event->accept();
    }
    else{
        int ret = QMessageBox::question(this, tr(QUIT_DIALOG_TITLE),
                                        tr(QUIT_MSG),
                                        QMessageBox::Ok | QMessageBox::Cancel, QMessageBox::Cancel);
        switch (ret) {
            case QMessageBox::Ok:
                event->accept();
                break;
            case QMessageBox::Cancel:
                event->ignore();
                break;
            default:
                break;
        }
    }
}

void ConfigurationDialog::reject()
{
    this->close();
}

void ConfigurationDialog::showError()
{
    ui->label_error->setText(tr(MISSING_PATHS_MSG));
    ui->label_error->show();
}

void ConfigurationDialog::confirm()
{
    mIsCloseable = true;
    this->close();
}

void ConfigurationDialog::slot_setProjectDir()
{
    mProjectDir = QFileDialog::getExistingDirectory(this, tr(PROJECT_SELECT_MSG));
    ui->label_projectsDir->setText(mProjectDir);
}

void ConfigurationDialog::slot_setClassificationPluginsDir()
{
    mClassificationPluginsDir = QFileDialog::getExistingDirectory(this, tr(CLASSIFICATION_SELECT_MSG));
    ui->label_classificationDir->setText(mClassificationPluginsDir);
}

void ConfigurationDialog::slot_setImageLoaderPluginsDir()
{
    mImageLoaderPluginsDir = QFileDialog::getExistingDirectory(this, tr(LOADER_SELECT_MSG));
    ui->label_imageLoaderDir->setText(mImageLoaderPluginsDir);
}

void ConfigurationDialog::slot_setPythonPath()
{
    mPythonPath = QFileDialog::getOpenFileName(this, tr(PYTHON_SELECT_MSG));
    ui->label_pythonPath->setText(mPythonPath);
}

void ConfigurationDialog::on_pushButton_apply_clicked(){
    emit sig_directoriesSpecified(mProjectDir, mClassificationPluginsDir, mImageLoaderPluginsDir, mPythonPath);
}
