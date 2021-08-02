#include "globalsettingswidget.h"
#include "ui_globalsettingswidget.h"

#include <QResizeEvent>

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
    QFontMetrics metrics(ui->label_projectsDir_new->font());
    QString text = metrics.elidedText(path, Qt::ElideRight, (parentWidget()->width() * 2) / 3);
    ui->label_projectsDir_new->setText(text);
}

void GlobalSettingsWidget::setNewClassificationPluginPath(QString path)
{
    QFontMetrics metrics(ui->label_classificationDir_new->font());
    QString text = metrics.elidedText(path, Qt::ElideRight, (parentWidget()->width() * 2) / 3);
    ui->label_classificationDir_new->setText(text);
}

void GlobalSettingsWidget::setNewImageLoaderPath(QString path)
{
    QFontMetrics metrics(ui->label_imageLoaderDir_new->font());
    QString text = metrics.elidedText(path, Qt::ElideRight, (parentWidget()->width() * 2) / 3);
    ui->label_imageLoaderDir_new->setText(text);
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
    QFontMetrics metrics(ui->label_projectsDir_current->font());
    QString text = metrics.elidedText(path, Qt::ElideRight, (parentWidget()->width() * 2) / 3);
    ui->label_projectsDir_current->setText(text);
}

void GlobalSettingsWidget::setCurrentClassificationDir(QString path)
{
    QFontMetrics metrics(ui->label_classificationDir_current->font());
    QString text = metrics.elidedText(path, Qt::ElideRight, (parentWidget()->width() * 2) / 3);
    ui->label_classificationDir_current->setText(text);
}

void GlobalSettingsWidget::setCurrentImageLoaderDir(QString path)
{
    QFontMetrics metrics(ui->label_imageLoaderDir_current->font());
    QString text = metrics.elidedText(path, Qt::ElideRight, (parentWidget()->width() * 2) / 3);
    ui->label_imageLoaderDir_current->setText(text);
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


void GlobalSettingsWidget::changeEvent(QEvent *event)
{
    if (event->type() == QEvent::LanguageChange) {
        // this event is sent if a translator is loaded
        QString tempProjects = ui->label_projectsDir_current->text();
        QString tempClassification = ui->label_classificationDir_current->text();
        QString tempImage = ui->label_imageLoaderDir_current->text();
        ui->retranslateUi(this);
        ui->label_projectsDir_current->setText(tempProjects);
        ui->label_classificationDir_current->setText(tempClassification);
        ui->label_imageLoaderDir_current->setText(tempImage);
        emit sig_wasTranslated();
    }

    // should be executed on resize but does nothing instead...
    //    QFontMetrics metrics(ui->label_imageLoaderDir_current->font());
    //    QString path =  ui->label_imageLoaderDir_current->text();
    //    QString text = metrics.elidedText(path, Qt::ElideRight, (parentWidget()->width() / 3) * 2);
    //    ui->label_imageLoaderDir_current->setText(text);

    //    path =  ui->label_imageLoaderDir_new->text();
    //    text = metrics.elidedText(path, Qt::ElideRight, (parentWidget()->width() / 3) * 2);
    //    ui->label_imageLoaderDir_new->setText(text);

    //    path =  ui->label_classificationDir_current->text();
    //    text = metrics.elidedText(path, Qt::ElideRight, (parentWidget()->width() / 3) * 2);
    //    ui->label_classificationDir_current->setText(text);

    //    path =  ui->label_classificationDir_new->text();
    //    text = metrics.elidedText(path, Qt::ElideRight,(parentWidget()->width() / 3) * 2);
    //    ui->label_classificationDir_new->setText(text);

    //    path =  ui->label_projectsDir_current->text();
    //    text = metrics.elidedText(path, Qt::ElideRight, (parentWidget()->width() / 3) * 2);
    //    ui->label_projectsDir_current->setText(text);

    //    path =  ui->label_projectsDir_new->text();
    //    text = metrics.elidedText(path, Qt::ElideRight, (parentWidget()->width() / 3) * 2);
    //    ui->label_projectsDir_new->setText(text);

    //Call to parent class
    QWidget::changeEvent(event);

}
