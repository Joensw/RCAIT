#include "mainwindow.h"
#include "ui_mainwindow.h"

MainWindow::MainWindow(QWidget *parent)
        : QMainWindow(parent),
          ui(new Ui::MainWindow),
          m_pushButton_settings(new QPushButton(this)) {
    ui->setupUi(this);

    centralWidget()->layout()->setContentsMargins(EDGE,EDGE,EDGE,EDGE);
    statusBar()->hide();

    //Spawn in screen center
    move(screen()->geometry().center() - frameGeometry().center());

    //Always start at first tab
    ui->tabWidget->setCurrentIndex(0);

    placeSettingsButton();
}

void MainWindow::placeSettingsButton() {
    connect(m_pushButton_settings, &QPushButton::clicked, this, &MainWindow::slot_settingsButton_clicked);

    m_pushButton_settings->setFlat(true);
    m_pushButton_settings->setIcon(QIcon(SETTINGSBUTTON_ICON));
    m_pushButton_settings->setIconSize(QSize(SETTINGSBUTTON_WIDTH, SETTINGSBUTTON_HEIGHT));
    ui->tabWidget->setCornerWidget(m_pushButton_settings, Qt::TopRightCorner);
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

ResultsWidget *MainWindow::getResultsWidget() {
    return ui->tab_results;
}

AutomationWidget *MainWindow::getAutomationWidget() {
    return ui->tab_automation;
}

ImageInspectionWidget *MainWindow::getImageInspectionWidget() {
    return ui->tab_image_inspection;
}

CustomTabWidget *MainWindow::getTabWidget() {
    return ui->tabWidget;
}

void MainWindow::slot_settingsButton_clicked() {
    emit sig_openSettings();
}

void MainWindow::slot_maximizeWindow() {
    this->setWindowState(Qt::WindowMaximized);
}

void MainWindow::slot_normalizeWindow() {
    this->setWindowState(Qt::WindowNoState);
}


void MainWindow::changeEvent(QEvent *event) {
    switch(event->type()) {
        case QEvent::LanguageChange:
            // this event is sent if a translator is loaded
            ui->retranslateUi(this);
            break;
        case QEvent::WindowStateChange:
            emit sig_changedWindowState(windowState());
            break;
        default:
            QMainWindow::changeEvent(event);
            break;
    }
}
