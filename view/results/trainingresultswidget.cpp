#include "trainingresultswidget.h"
#include "ui_trainingresultswidget.h"

TrainingResultsWidget::TrainingResultsWidget(QWidget *parent) :
    QWidget(parent),
    ui(new Ui::TrainingResultsWidget)
{
    ui->setupUi(this);

    connect(menu_addRun, &QMenu::triggered, this, &TrainingResultsWidget::slot_comparisonMenu_triggered);

    configure_compareRunButton();
    configure_compareRunMenu();


    //TODO: Remove dummy code
    dummyFunctionTest();
}

void TrainingResultsWidget::configure_compareRunMenu() {
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
}

void TrainingResultsWidget::configure_compareRunButton() {
    //Configure add run compare button
    const auto icon = QIcon(":/Resources/UISymbols/UI_Add_Result_Comparison_Icon.svg");
    pushButton_addResult->setIcon(icon);
    pushButton_addResult->setFlat(true);
    pushButton_addResult->setMenu(menu_addRun);
    ui->tabWidget_trainingresults->setCornerWidget(pushButton_addResult, Qt::TopRightCorner);
}

void TrainingResultsWidget::addTrainingResult(TrainingResult *result) {
    auto lossCurve = result->getLossCurve();
    auto confusionMatrix = result->getConfusionMatrix();
    auto mostMisclassifiedImages = result->getMostMisclassifiedImages();

    auto tab = createTrainingResultTab(result->getTimestamp());

    lossCurve->generateGraphics(tab);
    confusionMatrix->generateGraphics(tab);
    tab->setMostMisclassifiedImages(mostMisclassifiedImages);
}

TrainingResultsWidget::~TrainingResultsWidget()
{
    delete ui;
}

TopAccuraciesView* TrainingResultsWidget::getTopAccuraciesView(){
    return ui->tab_topAccuracies;
}

TrainingResultView *TrainingResultsWidget::createTrainingResultTab(const QString &tabName) {
    auto *tab = new TrainingResultView(this);
    ui->tabWidget_trainingresults->addTab(tab, tabName);
    m_mapTrainingResultTabs[tabName] = tab;
    return tab;
}

void TrainingResultsWidget::deleteTrainingResultTab(const QString &tabName) {
    auto *tabWidget = ui->tabWidget_trainingresults;
    auto tab = m_mapTrainingResultTabs.take(tabName);
    auto index = tabWidget->indexOf(tab);
    tabWidget->removeTab(index);
}

void TrainingResultsWidget::dummyFunctionTest() {
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
        QList<int> values = QList<int>();
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

void TrainingResultsWidget::slot_comparisonMenu_triggered(QAction *action) {
    auto topAccuracies = ui->tab_topAccuracies;
    const QString &runNameToCompare = action->text();
    if (action->isChecked()) {
        auto tab = createTrainingResultTab(runNameToCompare);
        emit sig_loadTrainingImagesToCompare(runNameToCompare, tab);
        emit sig_loadAccuracyDataToCompare(runNameToCompare, topAccuracies);
    } else {
        deleteTrainingResultTab(runNameToCompare);
        topAccuracies->removeTableRow(runNameToCompare);
    }
}

void TrainingResultsWidget::changeEvent(QEvent *event) {
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
void TrainingResultsWidget::retranslateUi() {
    pushButton_addResult->setText(tr("Compare ..."));
}
