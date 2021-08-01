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
    auto accCurve = result->getAccuracyCurve();
    auto confusionMatrix = result->getConfusionMatrix();
    auto mostMisclassifiedImages = result->getMostMisclassifiedImages();

    auto tab = createTrainingResultTab(result->getTimestamp());

    accCurve->generateGraphics(tab);
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

void TrainingResultsWidget::slot_comparisonMenu_triggered(QAction *action) {
    auto topAccuracies = ui->tab_topAccuracies;
    const QString &runNameToCompare = action->text();
    if (action->isChecked()) {
        auto tab = createTrainingResultTab(runNameToCompare);
        emit sig_loadTrainingImagesToCompare(runNameToCompare, tab);
        emit sig_loadAccuracyDataToCompare(runNameToCompare, topAccuracies);
    } else {
        deleteTrainingResultTab(runNameToCompare);
        emit sig_unloadAccuracyDataToCompare(runNameToCompare, topAccuracies);
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
