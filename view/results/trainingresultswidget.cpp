#include "trainingresultswidget.h"
#include "ui_trainingresultswidget.h"

//TODO Extract common methods/attributes in superclass
TrainingResultsWidget::TrainingResultsWidget(QWidget *parent) :
        QWidget(parent),
        ui(new Ui::TrainingResultsWidget) {
    ui->setupUi(this);

    connect(menu_addRun, &QMenu::triggered, this, &TrainingResultsWidget::slot_comparisonMenu_triggered);
    connect(ui->tabWidget_trainingresults, &QTabWidget::currentChanged, this,
            &TrainingResultsWidget::slot_updateSaveButton);

    configure_compareRunButton();
}

void TrainingResultsWidget::configure_compareRunMenu(const QString &resultsDirPath) {

    //Cleanup, because results dir was changed
    //Remove opened tabs
    for (const auto &action : menu_addRun->actions()) {
        if (action->isChecked()) {
            auto runName = action->text();
            removeComparisonResult(runName);
        }
    }
    //Clear menu entries
    menu_addRun->clear();

    //Add compare button menu entries
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

    auto tab = createTrainingResultTab(result->getIdentifier());

    accCurve->generateGraphics(tab);
    confusionMatrix->generateGraphics(tab);
    tab->setMostMisclassifiedImages(mostMisclassifiedImages);
}

TrainingResultsWidget::~TrainingResultsWidget() {
    delete ui;
}

TopAccuraciesView *TrainingResultsWidget::getTopAccuraciesView() {
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
    action->blockSignals(true);
    auto topAccuracies = ui->tab_topAccuracies;
    const QString &runNameToCompare = action->text();

    if (action->isChecked())
        addComparisonResult(runNameToCompare);
    else
        removeComparisonResult(runNameToCompare);
}

void TrainingResultsWidget::addComparisonResult(const QString &runNameToCompare) {
    auto topAccuracies = ui->tab_topAccuracies;
    auto tab = createTrainingResultTab(runNameToCompare);
    //TODO move to slot
    tab->setSaved(true);
    emit sig_comparison_loadTrainingResultGraphics(runNameToCompare, tab);
    emit sig_comparison_loadAccuracyData(runNameToCompare, topAccuracies);
}

void TrainingResultsWidget::removeComparisonResult(const QString &runNameToCompare) {
    deleteTrainingResultTab(runNameToCompare);
    auto topAccuracies = ui->tab_topAccuracies;
    emit sig_comparison_unloadAccuracyData(runNameToCompare, topAccuracies);
}

void TrainingResultsWidget::slot_updateSaveButton(int index) {
    auto widget = ui->tabWidget_trainingresults->widget(index);
    auto tab = dynamic_cast<AbstractGraphicsView *>(widget);
    auto saveButton = ui->pushButton_saveTrainingResults;

    saveButton->setEnabled(!tab->isSaved());
}

void TrainingResultsWidget::slot_updateResultFolderPaths(const QString &trainingResultsPath,
                                                         const QString &classificationResultsPath) {
    configure_compareRunMenu(trainingResultsPath);
}

void TrainingResultsWidget::changeEvent(QEvent *event) {
    if (event->type() == QEvent::LanguageChange) {
        // this event is sent if a translator is loaded
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