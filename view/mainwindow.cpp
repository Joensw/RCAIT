#include "mainwindow.h"
#include "ui_mainwindow.h"

MainWindow::MainWindow(QWidget *parent)
        : QMainWindow(parent), ui(new Ui::MainWindow) {
    ui->setupUi(this);

    centralWidget()->layout()->setContentsMargins(2, 2, 2, 2);
    statusBar()->hide();

    //Spawn in screen center
    move(screen()->geometry().center() - frameGeometry().center());

    //Always start at first tab
    ui->tabWidget->setCurrentIndex(0);

    placeSettingsButton();
}

void MainWindow::placeSettingsButton() {
    pushButton_settings->setFlat(true);
    pushButton_settings->setIcon(QIcon(":/Resources/TabIcons/Filled/Tab_Settings_Icon.svg"));
    pushButton_settings->setIconSize(QSize(32, 57));
    connect(pushButton_settings, &QPushButton::clicked, this, &MainWindow::slot_settingsButton_clicked);
    ui->tabWidget->setCornerWidget(pushButton_settings, Qt::TopRightCorner);
}

MainWindow::~MainWindow() {
    delete ui;
}

StartWidget *MainWindow::getStartWidget() {
    return ui->tab_start;
}

InputImagesWidget *MainWindow::getInputImagesWidget() {
    return ui->tab_inputimages;
}

AITrainingWidget *MainWindow::getAITrainingWidget() {
    return ui->tab_ai_training;
}

ImportFilesWidget *MainWindow::getImportFilesWidget() {
    return ui->tab_import;
}

ResultsWidget *MainWindow::getResultsWidget(){
    return ui->tab_results;
}

AutomationWidget *MainWindow::getAutomationWidget() {
    return ui->tab_automation;
}

void MainWindow::slot_settingsButton_clicked() {
    emit sig_openSettings();
}

void MainWindow::on_pushButton_openProject_clicked()
{
    int newIndex = ui->tabWidget->currentIndex() + 1;
    ui->tabWidget->setCurrentIndex(newIndex);
}

void MainWindow::changeEvent(QEvent *event) {
    if (event->type() == QEvent::LanguageChange) {
        // this event is send if a translator is loaded
        ui->retranslateUi(this);
    }
    QMainWindow::changeEvent(event);
}
