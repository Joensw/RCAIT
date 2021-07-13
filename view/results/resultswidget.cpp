#include <QPushButton>
#include <QMenu>
#include <QSplineSeries>
#include <QRandomGenerator>
#include "resultswidget.h"
#include "ui_resultswidget.h"
#include "confusionmatrix.h"
#include "projectmanager.h"

ResultsWidget::ResultsWidget(QWidget *parent) :
        QWidget(parent),
        ui(new Ui::ResultsWidget) {

    ui->setupUi(this);

    //Configure add run compare button
    const auto icon = QIcon(":/Resources/UISymbols/UI_Add_Result_Comparison_Icon.svg");
    pushButton_addResult->setIcon(icon);
    pushButton_addResult->setFlat(true);
    pushButton_addResult->setMenu(menu_addRun);
    connect(menu_addRun, &QMenu::triggered, this, &ResultsWidget::slot_comparisonMenu_triggered);
    ui->tabWidget_comparison->setCornerWidget(pushButton_addResult, Qt::TopRightCorner);

    //Add compare button menu entries
    auto resultsDirPath = ProjectManager::getInstance().getResultsDir();
    auto dir = QDir(resultsDirPath);
    auto entryList = dir.entryList(QDir::AllDirs | QDir::NoDotAndDotDot);

    for (const auto &item : entryList) {
        //Compare Run Button Menu
        auto *action = new QAction(item, menu_addRun);
        action->setCheckable(true);
        menu_addRun->addAction(action);
    }

    //TODO: Remove dummy code
    dummyFunctionTest();

    QTableWidget *table = ui->tableWidget_topAccuracy;
    QHeaderView *header = table->horizontalHeader();
    header->setSectionResizeMode(QHeaderView::Stretch);

}

void ResultsWidget::slot_comparisonMenu_triggered(QAction *action) {
    if (action->isChecked()) {
        addTrainingResultTab(action->text());
    } else {
        deleteTrainingResultTab(action->text());
    }
}

QString ResultsWidget::getSelectedTrainRunIdentifier() {
    return QString();
}

QString ResultsWidget::getSelectedClassifyRunIdentifier() {
    return QString();
}

void ResultsWidget::addTrainingResult(TrainingResult *result) {
    QString name = "Run";
    auto data_lossCurve = result->getLossCurveData();
    auto confusionMatrix = result->getConfusionMatrix();
    auto mostMisclassifiedImages = result->getMostMisclassifiedImages();

    auto tab = addTrainingResultTab(name);

    //Parse Loss curve
    auto series = parseLossCurveData(data_lossCurve);

    //Pass to Most Misclassified Images

//TODO: (Adrians Help) Pass QList<QImages>


    tab->setLossCurve(series.first, series.second);
    tab->setConfusionMatrix(confusionMatrix->generateConfusionMatrixGraphics("matrix.svg"));
    tab->setMostMisclassifiedImages(QList<QImage>());
}

QPair<QLineSeries *, QLineSeries *>
ResultsWidget::parseLossCurveData(const QMap<int, QPair<double, double>> &data_lossCurve) {
    auto *trainSeries = new QSplineSeries();
    auto *validationSeries = new QSplineSeries();

    for (const auto &xValue : data_lossCurve.keys()) {
        QPair<double, double> pair = data_lossCurve[xValue];
        auto yTrain = pair.first;
        auto yValidation = pair.second;
        auto trainPoint = QPointF(xValue, yTrain);
        auto validationPoint = QPointF(xValue, yValidation);

        *trainSeries << trainPoint;
        *validationSeries << validationPoint;
    }
    return qMakePair(trainSeries, validationSeries);
}

void ResultsWidget::addClassificationResult(ClassificationResult *result) {

}

ResultsWidget::~ResultsWidget() {
    delete ui;
}

TrainingResultView *ResultsWidget::addTrainingResultTab(const QString &tabName) {
    auto tab = new TrainingResultView(this);
    int index = ui->tabWidget_comparison->addTab(tab, tabName);
    m_mapTrainingResultTabs[tabName] = index;
    return tab;
}

void ResultsWidget::deleteTrainingResultTab(const QString &tabName) {
    auto *widget = ui->tabWidget_comparison;
    auto index = m_mapTrainingResultTabs.take(tabName);
    widget->removeTab(index);
}

void ResultsWidget::dummyFunctionTest() {
    for (int i = 0; i < 3; ++i) {
        QString run = QString("Run %1").arg(i + 1);
        auto tab = addTrainingResultTab(run);

        //Loss Curve
        auto *trainSeries = new QSplineSeries();
        auto *validationSeries = new QSplineSeries();
        int precision = 1;
        for (int j = 0; j < 20 * precision; j++) {
            double random = QRandomGenerator::global()->bounded(3 * 100) / 100.0;
            *validationSeries << QPointF((double) j / precision, random);
        }

        int sum = 0;
        for (int j = 0; j < 20 * precision; j++) {
            int random = QRandomGenerator::global()->bounded(-2, 15);
            sum += random;
            *trainSeries << QPointF((double) j / precision, 3 + 100 / (double) abs(sum));
        }
        tab->setLossCurve(trainSeries, validationSeries);

        //Confusion Matrix
        QList<double> values = QList<double>();
        QStringList labels = {"A", "B", "C", "D", "E", "F", "G", "H"};
        const qsizetype N = labels.size();
        for (int j = 0; j < N * N; ++j) {
            int random = QRandomGenerator::global()->bounded(0, 100);
            values << random;
        }

        auto matrix = new ConfusionMatrix(labels, values);
        auto item = matrix->generateConfusionMatrixGraphics("matrix_" + run + ".svg");
        tab->setConfusionMatrix(item);
    }
}

void ResultsWidget::changeEvent(QEvent *event) {
    if (event->type() == QEvent::LanguageChange) {
        // this event is send if a translator is loaded
        retranslateUi();
        ui->retranslateUi(this);
    }
    //Call to parent class
    QWidget::changeEvent(event);
}

/**
 * Translate and set all the strings which
 * were not created in the UI builder
 */
void ResultsWidget::retranslateUi() {
    pushButton_addResult->setText(tr("Compare ..."));
}
