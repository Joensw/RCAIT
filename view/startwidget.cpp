#include "startwidget.h"
#include "ui_startwidget.h"

#include <QDir>

StartWidget::StartWidget(QWidget *parent) :
    QWidget(parent),
    ui(new Ui::StartWidget)
{
    ui->setupUi(this);
    populateLanguageMenu(ui->comboBox_languageSelection);
}

StartWidget::~StartWidget()
{
    delete ui;
}

void StartWidget::populateLanguageMenu(QComboBox *box) {
    QDir dir(m_langPath);
    QStringList fileNames = dir.entryList(QStringList() << "*.qm", QDir::Files);

    for (auto &fileName : fileNames) {
        // get locale extracted by filename
        QString locale = fileName; // "TranslationExample_de.qm"
        locale.truncate(locale.lastIndexOf('.')); // "TranslationExample_de"
        locale.remove(0, locale.indexOf('_') + 1); // "de"

        QString lang = QLocale::languageToString(QLocale(locale).language());

        box->addItem(lang, locale);
    }
}


QString StartWidget::getLanguageEntry() {
    QComboBox *box = ui->comboBox_languageSelection;
    QString locale = box->currentData().toString();
    return locale;
}

void StartWidget::on_pushButton_newProject_clicked() {
    emit sig_newProject();
}

void StartWidget::on_pushButton_removeProject_clicked() {
    //if there are no projects dont do anything
    QListWidgetItem * item = ui->listWidget_projectsList->currentItem();
    if (!ui->listWidget_projectsList->count() || !item) {
        return;
    }
    QString toRemove = item->text();
    emit sig_removeProject(toRemove);
}


void StartWidget::addProjects(QStringList projects)
{
    ui->listWidget_projectsList->addItems(projects);
}

void StartWidget::addProject(QString project)
{
    ui->listWidget_projectsList->addItem(project);
}

void StartWidget::clearProjectList()
{
    ui->listWidget_projectsList->clear();
}

