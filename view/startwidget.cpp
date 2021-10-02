#include "startwidget.h"
#include "ui_startwidget.h"

#include <QDir>

StartWidget::StartWidget(QWidget *parent) :
        QWidget(parent), ui(new Ui::StartWidget){

    ui->setupUi(this);
    populateLanguageMenu(ui->comboBox_languageSelection);
    connect(ui->listWidget_projectsList, &QListWidget::itemSelectionChanged, this, &StartWidget::slot_setEnableActionButtons);
}

StartWidget::~StartWidget() {
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

void StartWidget::on_comboBox_languageSelection_currentTextChanged(const QString &arg1) {
    Q_UNUSED(arg1)
    loadLanguage(getLanguageEntry());
    //Update UI after loading language is necessary
    ui->retranslateUi(this);
}

void StartWidget::on_pushButton_newProject_clicked() {
    emit sig_newProject();
}

void StartWidget::on_pushButton_removeProject_clicked() {
    //if there are no projects, or no current item, dont do anything
    QListWidgetItem *item = ui->listWidget_projectsList->currentItem();
    if (item) {
        QString toRemove = item->text();
        emit sig_removeProject(toRemove);
    }
}

void StartWidget::on_pushButton_openProject_clicked() {
    QListWidgetItem *item = ui->listWidget_projectsList->currentItem();
    if (item) {
        QString toOpen = item->text();
        emit sig_openProject(toOpen);
    }
}


void StartWidget::addProjects(QStringList projects) {
    ui->listWidget_projectsList->addItems(projects);
}

void StartWidget::addProject(QString project) {
    ui->listWidget_projectsList->addItem(project);
}

void StartWidget::clearProjectList() {
    ui->listWidget_projectsList->clear();
}

void StartWidget::setActionButtonsEnabled(bool state)
{
    ui->pushButton_openProject->setEnabled(state);
    ui->pushButton_removeProject->setEnabled(state);
}

void StartWidget::resetListSelection()
{
    ui->listWidget_projectsList->setCurrentRow(QLISTWIDGET_UNSELECT_INDEX);
}


void StartWidget::loadLanguage(const QString &rLanguage) {
    if (m_currLang != rLanguage) {
        m_currLang = rLanguage;
        QLocale locale = QLocale(m_currLang);
        QLocale::setDefault(locale);
        switchTranslator(m_translator, rLanguage);
    }
}

void StartWidget::switchTranslator(QTranslator &translator, const QString &filename) {
    const QString baseName = qApp->applicationName() + "_" + filename;
    if (translator.load(m_langPath + baseName)) {
        qApp->removeTranslator(&translator);
        qApp->installTranslator(&translator);
    }
}


void StartWidget::on_pushButton_toggleFullscreen_toggled(bool checked) {
    if (checked)
            emit sig_maximizeWindow();
    else
            emit sig_normalizeWindow();
}

void StartWidget::slot_changedWindowState(Qt::WindowStates flags) {
    auto fullscreenButton = ui->pushButton_toggleFullscreen;
    switch (flags) {
        case Qt::WindowMaximized:
            fullscreenButton->setChecked(true);
            break;
        case Qt::WindowNoState:
            fullscreenButton->setChecked(false);
            break;
    }
}

void StartWidget::slot_imagesUpdated()
{
    if (!(ui->listWidget_projectsList->selectedItems().size() == 0)){
        ui->pushButton_openProject->setEnabled(true);
    }
}

void StartWidget::slot_startLoading()
{
    ui->pushButton_openProject->setEnabled(false);
}

void StartWidget::slot_setEnableActionButtons()
{
    setActionButtonsEnabled(true);
}
