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
        int ret = QMessageBox::question(this, tr("Quit confirmation"),
                                        tr("Are you sure you want to quit?\n" "The application will terminate"),
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
    ui->label_error->setText(tr("Please specifiy all paths uniquely before proceeding."));
    ui->label_error->show();
}

void ConfigurationDialog::confirm()
{
    mIsCloseable = true;
    this->close();
}


//Todo empty string
void ConfigurationDialog::slot_setProjectDir()
{
    mProjectDir = QFileDialog::getExistingDirectory(this, tr("Select project directory"));
    ui->label_projectsDir->setText(mProjectDir);
}

void ConfigurationDialog::slot_setClassificationPluginsDir()
{
    mClassificationPluginsDir = QFileDialog::getExistingDirectory(this, tr("Select classification plugin directory"));
    ui->label_classificationDir->setText(mClassificationPluginsDir);
}

void ConfigurationDialog::slot_setImageLoaderPluginsDir()
{
    mImageLoaderPluginsDir = QFileDialog::getExistingDirectory(this, tr("Select image-loader plugin directory"));
    ui->label_imageLoaderDir->setText(mImageLoaderPluginsDir);
}

void ConfigurationDialog::on_pushButton_apply_clicked(){
    emit sig_directoriesSpecified(mProjectDir, mClassificationPluginsDir, mImageLoaderPluginsDir);
}
