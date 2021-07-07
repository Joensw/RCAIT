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

void StartWidget::on_pushButton_newProject_clicked(){
    NewProjectDialog projectDialog;
    //apparently exec is not that great, possibly find an alternative and hold the object longer
    projectDialog.exec();

}