#include "globalsettingswidget.h"
#include "ui_globalsettingswidget.h"

#include <QResizeEvent>

GlobalSettingsWidget::GlobalSettingsWidget(QWidget *parent) :
        QWidget(parent),
        ui(new Ui::GlobalSettingsWidget) {
    ui->setupUi(this);
}

GlobalSettingsWidget::~GlobalSettingsWidget() {
    delete ui;
}

void GlobalSettingsWidget::setNewProjectPath(const QString &path) {
    QFontMetrics metrics(ui->label_projectsDir_new->font());
    QString text = metrics.elidedText(path, Qt::ElideRight, (parentWidget()->width() * 2) / 3);
    ui->label_projectsDir_new->setText(text);
}

void GlobalSettingsWidget::setNewClassificationPluginPath(const QString &path) {
    QFontMetrics metrics(ui->label_classificationDir_new->font());
    QString text = metrics.elidedText(path, Qt::ElideRight, (parentWidget()->width() * 2) / 3);
    ui->label_classificationDir_new->setText(text);
}

void GlobalSettingsWidget::setNewImageLoaderPath(const QString &path) {
    QFontMetrics metrics(ui->label_imageLoaderDir_new->font());
    QString text = metrics.elidedText(path, Qt::ElideRight, (parentWidget()->width() * 2) / 3);
    ui->label_imageLoaderDir_new->setText(text);
}

void GlobalSettingsWidget::setNewPythonPath(const QString &path) {
    QFontMetrics metrics(ui->label_pythonPath_new->font());
    QString text = metrics.elidedText(path, Qt::ElideRight, (parentWidget()->width() * 2) / 3);
    ui->label_pythonPath_new->setText(text);
}

void GlobalSettingsWidget::clearNewPaths() {
    ui->label_projectsDir_new->clear();
    ui->label_classificationDir_new->clear();
    ui->label_imageLoaderDir_new->clear();
    ui->label_pythonPath_new->clear();
}

void GlobalSettingsWidget::showUpdate(int amount) {
    ui->label_information->clear();
    if (amount == 0) {
        ui->label_information->setStyleSheet(STYLESHEET_BLUE);
        ui->label_information->setText(tr(NO_CHANGES_MSG));
    } else {
        ui->label_information->setStyleSheet(STYLESHEET_GREEN);
        ui->label_information->setText(tr(SUCCESS_UPDATED_PATHS_MSG, "", amount));
    }
}

void GlobalSettingsWidget::setError(const QString &error) {
    ui->label_information->clear();
    ui->label_information->setStyleSheet(STYLESHEET_RED);
    ui->label_information->setText(error);
}

void GlobalSettingsWidget::setCurrentProjectsDir(const QString &path) {
    QFontMetrics metrics(ui->label_projectsDir_current->font());
    QString text = metrics.elidedText(path, Qt::ElideRight, (parentWidget()->width() * 2) / 3);
    ui->label_projectsDir_current->setText(text);
}

void GlobalSettingsWidget::setCurrentClassificationDir(const QString &path) {
    QFontMetrics metrics(ui->label_classificationDir_current->font());
    QString text = metrics.elidedText(path, Qt::ElideRight, (parentWidget()->width() * 2) / 3);
    ui->label_classificationDir_current->setText(text);
}

void GlobalSettingsWidget::setCurrentImageLoaderDir(const QString &path) {
    QFontMetrics metrics(ui->label_imageLoaderDir_current->font());
    QString text = metrics.elidedText(path, Qt::ElideRight, (parentWidget()->width() * 2) / 3);
    ui->label_imageLoaderDir_current->setText(text);
}

void GlobalSettingsWidget::setCurrentPythonPath(const QString &path) {
    QFontMetrics metrics(ui->label_pythonPath_current->font());
    QString text = metrics.elidedText(path, Qt::ElideRight, (parentWidget()->width() * 2) / 3);
    ui->label_pythonPath_current->setText(text);
}

void GlobalSettingsWidget::on_pushButton_project_clicked() {
    emit sig_setProjectDir();
}

void GlobalSettingsWidget::on_pushButton_classification_clicked() {
    emit sig_setClassificationPluginsDir();
}

void GlobalSettingsWidget::on_pushButton_imageLoader_clicked() {
    emit sig_setImageLoaderPluginsDir();
}

void GlobalSettingsWidget::on_pushButton_python_clicked(){
    emit sig_setGeneralPythonPath();
}

void GlobalSettingsWidget::changeEvent(QEvent *event) {
    if (event->type() == QEvent::LanguageChange) {
        // this event is sent if a translator is loaded
        ui->retranslateUi(this);
    }

    //Call to parent class
    QWidget::changeEvent(event);
}

