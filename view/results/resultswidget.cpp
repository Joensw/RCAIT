#include <QPushButton>
#include <QMenu>
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
    auto lossCurve = result->getLossCurve();
    auto confusionMatrix = result->getConfusionMatrix();
    auto mostMisclassifiedImages = result->getMostMisclassifiedImages();

    auto tab = addTrainingResultTab(name);


    //Pass to Most Misclassified Images

//TODO: (Adrians Help) Pass QList<QImages>


    tab->setLossCurve(confusionMatrix->generateConfusionMatrixGraphics("losscurve.svg"));
    tab->setConfusionMatrix(confusionMatrix->generateConfusionMatrixGraphics("matrix.svg"));
    tab->setMostMisclassifiedImages(QList<QImage>());
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
        int sum = 0;
        auto *pointsMap = new QMap<int, QPair<double, double>>();
        for (int j = 0; j < 20; j++) {
            double random = QRandomGenerator::global()->bounded(3 * 100) / 100.0;
            int random2 = QRandomGenerator::global()->bounded(-2, 15);
            sum += random2;
            pointsMap->insert(j,qMakePair(100 / (double) abs(sum),random));
        }
        auto lossCurve = new LossCurve(*pointsMap);
        auto itemLC = lossCurve->generateLossCurveGraphics("losscurve_" + run + ".svg");
        tab->setLossCurve(itemLC);

        //Confusion Matrix
        QList<double> values = QList<double>();
        QStringList labels = {"A", "B", "C", "D", "E", "F", "G", "H"};
        const qsizetype N = labels.size();
        qsizetype target = 0;
        for (int j = 0; j < N * N; ++j) {
            //Check if we are on diagonal line of matrix
            int min = 0;
            int max = 10;
            if (target == j){
                target += N+1;
                min = 30;
                max = 100;
            }
            int random = QRandomGenerator::global()->bounded(min, max);
            values << random;
        }

        auto matrix = new ConfusionMatrix(labels, values);
        auto itemCM = matrix->generateConfusionMatrixGraphics("matrix_" + run + ".svg");
        tab->setConfusionMatrix(itemCM);
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
