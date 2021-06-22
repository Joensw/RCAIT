#include <QGraphicsSvgItem>
#include <QRandomGenerator>
#include <QSplineSeries>
#include <QValueAxis>
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

void MainWindow::populateResultCharts() {
    QChartView *views[2] = {ui->graphicsView_losscurve, ui->graphicsView_losscurve_2};
    QString colors[2] = {"orange", "green"};

    for (int i = 0; i < 2; ++i) {
//        views[i]->layout()->setContentsMargins(0, 0, 0, 0);

        auto *trainSeries = new QSplineSeries();
        auto *validationSeries = new QSplineSeries();
        QPen pen = validationSeries->pen();
        pen.setWidth(3);
        validationSeries->setPen(pen);
        validationSeries->setColor(colors[i]);
        int precision = 1;
        for (int j = 0; j < 20*precision; j++) {
            double random = QRandomGenerator::global()->bounded(3*100)/100.0;
            *validationSeries << QPointF((double) j / precision, random);
        }

        int sum = 0;
        for (int j = 0; j < 20*precision; j++) {
            int random = QRandomGenerator::global()->bounded(-2,15);
            sum += random;
            *trainSeries << QPointF((double) j / precision, 3+ 100 / (double) abs(sum));
        }

        QChart *chart = views[i]->chart();
        chart->setBackgroundRoundness(0);

        chart->legend()->hide();
        chart->addSeries(trainSeries);
        chart->addSeries(validationSeries);

        auto *axisY = new QValueAxis();
        axisY->setLabelFormat("%.0f");
        chart->addAxis(axisY, Qt::AlignLeft);
        trainSeries->attachAxis(axisY);
        validationSeries->attachAxis(axisY);
        axisY->applyNiceNumbers();
        axisY->setMin(0);

        auto *axisX = new QValueAxis();
        axisX->setLabelFormat("%.0f");
        chart->addAxis(axisX, Qt::AlignBottom);
        trainSeries->attachAxis(axisX);
        validationSeries->attachAxis(axisX);
        axisX->applyNiceNumbers();

        views[i]->setRenderHint(QPainter::Antialiasing);
        chart->setAnimationOptions(QChart::AllAnimations);
    }
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

void MainWindow::populateConfusionMatrix() {
    QGraphicsView *views[2] = {ui->graphicsView_confusionmatrix, ui->graphicsView_confusionmatrix_2};
    QString paths[2] = {":/Resources/UISymbols/confusionmatrix.svg",":/Resources/UISymbols/confusionmatrix2.svg"};
    for (int i = 0; i < 2; ++i) {
        QString path = paths[i];
        auto *item = new QGraphicsSvgItem(path);
        auto *scene = new QGraphicsScene;
        QGraphicsView *view = views[i];
        view->scale(0.8, 0.8);

        scene->addItem(item);
        view->setHorizontalScrollBarPolicy(Qt::ScrollBarAlwaysOff);
        view->setVerticalScrollBarPolicy(Qt::ScrollBarAlwaysOff);
        view->fitInView(scene->sceneRect(), Qt::KeepAspectRatio);
        view->setScene(scene);
    }
}

