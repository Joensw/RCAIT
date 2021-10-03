#include "globalsettingswidget.h"
#include "ui_globalsettingswidget.h"

GlobalSettingsWidget::GlobalSettingsWidget(QWidget *parent) :
        QWidget(parent),
        ui(new Ui::GlobalSettingsWidget) {
    ui->setupUi(this);
}

GlobalSettingsWidget::~GlobalSettingsWidget() {
    delete ui;
}

void GlobalSettingsWidget::setNewProjectPath(const QString &path) {
    setText(path, ui->label_projectsDir_new);
}

void GlobalSettingsWidget::setNewClassificationPluginPath(const QString &path) {
    setText(path, ui->label_classificationDir_new);
}

void GlobalSettingsWidget::setNewImageLoaderPath(const QString &path) {
    setText(path, ui->label_imageLoaderDir_new);
}

void GlobalSettingsWidget::setNewPythonPath(const QString &path) {
    setText(path, ui->label_pythonPath_new);
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
        QString message = SUCCESS_UPDATED_PATHS_MSG;
        ui->label_information->setText(message.arg(amount));

    }
}

void GlobalSettingsWidget::setError(const QString &error) {
    ui->label_information->clear();
    ui->label_information->setStyleSheet(STYLESHEET_RED);
    ui->label_information->setText(error);
}

void GlobalSettingsWidget::setCurrentProjectsDir(const QString &path) {
    setText(path, ui->label_projectsDir_current);
}

void GlobalSettingsWidget::setCurrentClassificationDir(const QString &path) {
    setText(path, ui->label_classificationDir_current);
}

void GlobalSettingsWidget::setCurrentImageLoaderDir(const QString &path) {
    setText(path, ui->label_imageLoaderDir_current);
}

void GlobalSettingsWidget::setCurrentPythonPath(const QString &path) {
    setText(path, ui->label_pythonPath_current);
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

void GlobalSettingsWidget::setText(const QString &path, QLabel *label)
{
    QFontMetrics metrics(label->font());
    QString text = metrics.elidedText(path, Qt::ElideRight, (parentWidget()->width() * 2) / 3);
    label->setText(text);

}

void GlobalSettingsWidget::changeEvent(QEvent *event) {
    if (event->type() == QEvent::LanguageChange) {
        // this event is sent if a translator is loaded
        ui->retranslateUi(this);
    }

    //Call to parent class
    QWidget::changeEvent(event);
}

