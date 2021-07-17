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

}

void ResultsWidget::slot_comparisonMenu_triggered(QAction *action) {
    if (action->isChecked()) {
        createTrainingResultTab(action->text());
        ui->tab_topAccuracy->addTableRow(action->text(), 12.34, 56.78);
    } else {
        deleteTrainingResultTab(action->text());
        ui->tab_topAccuracy->removeTableRow(action->text());
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

    auto tab = createTrainingResultTab(name);


    //Pass to Most Misclassified Images

//TODO: (Adrians Help) Pass QList<QImages>

    lossCurve->generateGraphics(tab);
    confusionMatrix->generateGraphics(tab);
    tab->setMostMisclassifiedImages(QList<QImage>());
}

void ResultsWidget::addClassificationResult(ClassificationResult *result) {

}

ResultsWidget::~ResultsWidget() {
    delete ui;
}

TrainingResultView *ResultsWidget::createTrainingResultTab(const QString &tabName) {
    auto *tab = new TrainingResultView(this);
    ui->tabWidget_comparison->addTab(tab, tabName);
    m_mapTrainingResultTabs[tabName] = tab;
    return tab;
}

void ResultsWidget::deleteTrainingResultTab(const QString &tabName) {
    auto *tabWidget = ui->tabWidget_comparison;
    auto tab = m_mapTrainingResultTabs.take(tabName);
    auto index = tabWidget->indexOf(tab);
    tabWidget->removeTab(index);
}

void ResultsWidget::dummyFunctionTest() {
    for (int i = 0; i < 3; ++i) {
        QString run = QString("Run %1").arg(i + 1);
        auto tab = createTrainingResultTab(run);

        //Loss Curve
        int sum = 0;
        auto *pointsMap = new QMap<int, QPair<double, double>>();
        for (int j = 1; j <= 20; j++) {
            double random = QRandomGenerator::global()->bounded(3 * 100) / 100.0;
            int random2 = QRandomGenerator::global()->bounded(-2, 10);
            sum += random2;
            pointsMap->insert(j, qMakePair(100 / (double) abs(sum) + 3, random));
        }
        auto lossCurve = new LossCurve(run, *pointsMap);
        lossCurve->generateGraphics(tab);

        //Confusion Matrix
        QList<double> values = QList<double>();
        QStringList labels = {"A", "B", "C", "D", "E", "F", "G", "H"};
        const qsizetype N = labels.size();
        qsizetype target = 0;
        for (int j = 0; j < N * N; ++j) {
            //Check if we are on diagonal line of matrix
            int min = 0;
            int max = 10;
            if (target == j) {
                target += N + 1;
                min = 30;
                max = 100;
            }
            int random = QRandomGenerator::global()->bounded(min, max);
            values << random;
        }

        auto matrix = new ConfusionMatrix(run, labels, values);
        matrix->generateGraphics(tab);
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
