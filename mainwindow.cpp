#include "mainwindow.h"
#include "ui_mainwindow.h"
#include "themewidget.h"

MainWindow::MainWindow(QWidget *parent)
    : QMainWindow(parent)
    , ui(new Ui::MainWindow)
{
    ui->setupUi(this);
    ui->tabWidget->setCurrentIndex(0);

    populateLanguageMenu(ui->comboBox_languageSelection);
    populateResultCharts(ui);
}

void MainWindow::populateResultCharts(Ui::MainWindow *ui){
    //QChart *chart1 = ui->graph1->chart();

    //![1]
    QPieSeries *series = new QPieSeries();
    series->append("Truck", 1);
    series->append("Boat", 2);
    series->append("Bike", 3);
    series->append("Airplane", 4);
    series->append("Car", 5);
    //![1]

    //![2]
    QPieSlice *slice = series->slices().at(4);
    slice->setExploded();
    slice->setLabelVisible();
    slice->setPen(QPen(Qt::darkCyan, 2));
    slice->setBrush(Qt::cyan);
    //![2]

    //![3]
//    chart1->addSeries(series);
//    chart1->setTitle("Classification");
//    chart1->legend()->hide();
    //![3]


    //![1]
    QLineSeries *series2 = new QLineSeries();
    QLineSeries *series3 = new QLineSeries();
    series3->setColor("orange");
    //![1]

    //![2]
    series3->append(0, 1);
    series3->append(2, 1.5);
    series3->append(3, 2);
    series3->append(7, 1.5);
    series3->append(10, 2);
    *series3 << QPointF(11, 2) << QPointF(13, 1.5) << QPointF(17, 2) << QPointF(18, 2.5) << QPointF(20, 2);
    //![2]
    //![2]
    series2->append(0, 11);
    series2->append(1, 9);
    series2->append(2, 8);
    series2->append(3, 5);
    series2->append(5, 4.5);
    series2->append(7, 4);
    series2->append(10, 4);
    *series2 << QPointF(11, 3.5) << QPointF(13, 3) << QPointF(17, 4.2) << QPointF(18, 4) << QPointF(20, 3.9);
    //![2]

    //![3]
    QChart *chart2 = ui->graph2->chart();
    chart2->legend()->hide();
    chart2->addSeries(series2);
    chart2->addSeries(series3);
    chart2->createDefaultAxes();
    chart2->setTitle("Loss Curve Chart");

    //![3]

    //![4]
    //ui->graph1->setRenderHint(QPainter::Antialiasing);
    ui->graph2->setRenderHint(QPainter::Antialiasing);
//    chart1->setAnimationOptions(QChart::AllAnimations);
    chart2->setAnimationOptions(QChart::AllAnimations);
    //![4]
}

void MainWindow::populateLanguageMenu(QComboBox *box){
    QDir dir(m_langPath);
    QStringList fileNames = dir.entryList(QStringList() << "*.qm", QDir::Files);

    for (int i = 0; i < fileNames.size(); ++i)
    {
        // get locale extracted by filename
        QString locale;
        locale = fileNames[i]; // "TranslationExample_de.qm"
        locale.truncate(locale.lastIndexOf('.')); // "TranslationExample_de"
        locale.remove(0, locale.indexOf('_') + 1); // "de"

        QString lang = QLocale::languageToString(QLocale(locale).language());

        box->addItem(lang,locale);
    }
}

void MainWindow::switchTranslator(QTranslator& translator, const QString& filename) {

    const QString baseName = qApp->applicationName() +"_" + filename;
    if (translator.load(m_langPath + baseName)) {
        qApp->removeTranslator(&translator);
        qApp->installTranslator(&translator);
    }
}

void MainWindow::loadLanguage(const QString& rLanguage) {

    if(m_currLang != rLanguage)
    {
        m_currLang = rLanguage;
        QLocale locale = QLocale(m_currLang);
        QLocale::setDefault(locale);
        switchTranslator(m_translator, rLanguage);
    }
}


MainWindow::~MainWindow()
{
    delete ui;
}

void MainWindow::on_pushButton_2_clicked()
{
    int curr = ui->tabWidget->currentIndex();
    ui->tabWidget->setCurrentIndex(++curr);
}

void MainWindow::on_pushButton_clearTags_clicked()
{
    std::vector<QString> tags ;
    ui->lineEdit->tags(tags);
}

void MainWindow::on_comboBox_languageSelection_currentTextChanged(const QString &arg1)
{
    Q_UNUSED(arg1);
    QComboBox *box = ui->comboBox_languageSelection;
    QString locale = box->currentData().toString();
    loadLanguage(locale);
    //Update UI after loading language is necessary
    ui->retranslateUi(this);
}

