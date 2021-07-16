#include "globalsettingswidget.h"
#include "ui_globalsettingswidget.h"

GlobalSettingsWidget::GlobalSettingsWidget(QWidget *parent) :
    QWidget(parent),
    ui(new Ui::GlobalSettingsWidget)
{
    ui->setupUi(this);
}

GlobalSettingsWidget::~GlobalSettingsWidget()
{
    delete ui;
}

void GlobalSettingsWidget::setNewProjectPath(QString path)
{
    ui->label_projectsDir_new->setText(path);
}

void GlobalSettingsWidget::setNewClassificationPluginPath(QString path)
{
    ui->label_classificationDir_new->setText(path);
}

void GlobalSettingsWidget::setNewImageLoaderPath(QString path)
{
    ui->label_imageLoaderDir_new->setText(path);
}

void GlobalSettingsWidget::clearNewPaths()
{
    ui->label_projectsDir_new->setText("-");
    ui->label_classificationDir_new->setText("-");
    ui->label_imageLoaderDir_new->setText("-");
}

void GlobalSettingsWidget::showUpdate(int amount)
{
    if (amount == 0) {
        ui->label_information->setText("no changes were made");
        return;
    }
    ui->label_information->setText("Sucess. Updated " + QString::number(amount) + " path(s)");
}

void GlobalSettingsWidget::on_pushButton_project_clicked()
{
    emit sig_setProjectDir();
}

void GlobalSettingsWidget::on_pushButton_classification_clicked()
{
    emit sig_setClassificationPluginsDir();
}

void GlobalSettingsWidget::on_pushButton_imageLoader_clicked()
{
    emit sig_setImageLoaderPluginsDir();
}
