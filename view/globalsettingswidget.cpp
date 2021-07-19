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
    ui->label_information->clear();
    ui->label_information->setStyleSheet("QLabel { color : green; }");
    ui->label_information->setText(tr("Sucess. Updated ") + QString::number(amount) + tr(" path(s)"));
}

void GlobalSettingsWidget::showNonUpdate()
{
    ui->label_information->clear();
    ui->label_information->setStyleSheet("QLabel { color : blue; }");
    ui->label_information->setText(tr("no changes were made"));
}

void GlobalSettingsWidget::setError(QString error)
{
    ui->label_information->clear();
    ui->label_information->setStyleSheet("QLabel { color : red; }");
    ui->label_information->setText(error);
}

void GlobalSettingsWidget::setCurrentProjectsDir(QString path)
{
    ui->label_projectsDir_current->setText(path);
}

void GlobalSettingsWidget::setCurrentClassificationDir(QString path)
{
    ui->label_classificationDir_current->setText(path);
}

void GlobalSettingsWidget::setCurrentImageLoaderDir(QString path)
{
    ui->label_imageLoaderDir_current->setText(path);
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

void GlobalSettingsWidget::changeEvent(QEvent *event) {
    if (event->type() == QEvent::LanguageChange) {
        // this event is send if a translator is loaded
        QString tempProjects = ui->label_projectsDir_current->text();
        QString tempClassification = ui->label_classificationDir_current->text();
        QString tempImage = ui->label_imageLoaderDir_current->text();
        ui->retranslateUi(this);
        ui->label_projectsDir_current->setText(tempProjects);
        ui->label_classificationDir_current->setText(tempClassification);
        ui->label_imageLoaderDir_current->setText(tempImage);
        emit sig_wasTranslated();
    }
    //Call to parent class
    QWidget::changeEvent(event);
}
