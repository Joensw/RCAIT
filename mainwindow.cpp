#include "mainwindow.h"
#include "ui_mainwindow.h"
#include "themewidget.h"

MainWindow::MainWindow(QWidget *parent)
        : QMainWindow(parent), ui(new Ui::MainWindow) {
    ui->setupUi(this);

    //Spawn in screen center
    move(screen()->geometry().center() - frameGeometry().center());

    //Always start at first tab
    ui->tabWidget->setCurrentIndex(0);
    ui->tableWidget_2->horizontalHeader()->setSectionResizeMode( 0, QHeaderView::Stretch );
    ui->tableWidget_2->verticalHeader()->setSectionResizeMode( 0, QHeaderView::Stretch );

    populateLanguageMenu(ui->comboBox_languageSelection);
    populateResultCharts(ui);
    placeSettingsButton();
}

void MainWindow::placeSettingsButton() {
    pushButton_settings->setParent(this);
    pushButton_settings->setFlat(true);
    pushButton_settings->setIcon(QIcon(":/Resources/TabIcons/Filled/Tab_Settings_Icon.svg"));
    pushButton_settings->setIconSize(QSize(32, 57));
    ui->tabWidget->setCornerWidget(pushButton_settings, Qt::TopRightCorner);
}

void MainWindow::populateResultCharts(Ui::MainWindow *ui) {
    auto *series2 = new QLineSeries();
    auto *series3 = new QLineSeries();
    series3->setColor("orange");

    series3->append(0, 1);
    series3->append(2, 1.5);
    series3->append(3, 2);
    series3->append(7, 1.5);
    series3->append(10, 2);
    *series3 << QPointF(11, 2) << QPointF(13, 1.5) << QPointF(17, 2) << QPointF(18, 2.5) << QPointF(20, 2);

    series2->append(0, 11);
    series2->append(1, 9);
    series2->append(2, 8);
    series2->append(3, 5);
    series2->append(5, 4.5);
    series2->append(7, 4);
    series2->append(10, 4);
    *series2 << QPointF(11, 3.5) << QPointF(13, 3) << QPointF(17, 4.2) << QPointF(18, 4) << QPointF(20, 3.9);

    QChart *chart2 = ui->graph2->chart();
    chart2->legend()->hide();
    chart2->addSeries(series2);
    chart2->addSeries(series3);
    chart2->createDefaultAxes();
    chart2->setTitle("Loss Curve Chart");

    ui->graph2->setRenderHint(QPainter::Antialiasing);
    chart2->setAnimationOptions(QChart::AllAnimations);
}

void MainWindow::populateLanguageMenu(QComboBox *box) {
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

void MainWindow::switchTranslator(QTranslator &translator, const QString &filename) {

    const QString baseName = qApp->applicationName() + "_" + filename;
    if (translator.load(m_langPath + baseName)) {
        qApp->removeTranslator(&translator);
        qApp->installTranslator(&translator);
    }
}

void MainWindow::loadLanguage(const QString &rLanguage) {

    if (m_currLang != rLanguage) {
        m_currLang = rLanguage;
        QLocale locale = QLocale(m_currLang);
        QLocale::setDefault(locale);
        switchTranslator(m_translator, rLanguage);
    }
}


MainWindow::~MainWindow() {
    delete ui;
}

void MainWindow::on_pushButton_2_clicked() {
    int curr = ui->tabWidget->currentIndex();
    ui->tabWidget->setCurrentIndex(++curr);
}

void MainWindow::on_pushButton_clearTags_clicked() {
    std::vector<QString> tags;
    ui->lineEdit->tags(tags);
}

void MainWindow::on_comboBox_languageSelection_currentTextChanged(const QString &arg1) {
    Q_UNUSED(arg1)
    QComboBox *box = ui->comboBox_languageSelection;
    QString locale = box->currentData().toString();
    loadLanguage(locale);
    //Update UI after loading language is necessary
    ui->retranslateUi(this);
}

