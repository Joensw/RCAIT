#include "trainingresultswidget.h"

TrainingResultsWidget::TrainingResultsWidget(QWidget *parent)
        : GenericComparisonWidget(parent) {

    //Top Accuracies Tab configuration
    configure_topAccuraciesTab();
    connect(&*m_topAccuraciesView, &TopAccuraciesView::sig_normal_requestTopAccuraciesGraphics, this,
            &TrainingResultsWidget::slot_normal_requestTopAccuraciesGraphics);
}

void TrainingResultsWidget::configure_topAccuraciesTab() {
    const auto icon = QIcon(":/Resources/TabIcons/Filled/Results_Accuracy_Tab_Icon.svg");

    //Old pointer will go out of scope after leaving this method and gets auto-deleted
    m_topAccuraciesView.reset(new TopAccuraciesView(this));

    getTabWidget()->insertTab(0, &*m_topAccuraciesView, icon, QString());
    //Top Accuracies Tab cannot be saved in initial (= empty) state
    m_topAccuraciesView->setSaved(true);
}

void TrainingResultsWidget::updateResultFolderPath(const QString &newDirPath) {
    GenericComparisonWidget::updateResultFolderPath(newDirPath);

    auto &pm = ProjectManager::getInstance();
    //Old pointer will go out of scope after leaving this method and gets auto-deleted
    m_topAccuraciesGraphics.reset(new TopAccuraciesGraphics(pm.getProjectImageTempDir()));
}

void TrainingResultsWidget::addTrainingResult(TrainingResult *result) {
    auto tab = createResultTab<TrainingResultView>(result->getIdentifier());
    m_mapResultsByTab[tab] = result;
    emit sig_normal_generateTrainingResultGraphics(tab, result);
    emit sig_normal_loadTrainingResultData(tab, result);
}

void TrainingResultsWidget::addComparisonResult(const QString &runNameToCompare) {
    auto tab = createResultTab<TrainingResultView>(runNameToCompare);
    emit sig_comparison_loadTrainingResultGraphics(tab, runNameToCompare);
    emit sig_comparison_loadTrainingResultData(tab, runNameToCompare);
    emit sig_comparison_loadAccuracyData(&*m_topAccuraciesView, &*m_topAccuraciesGraphics, runNameToCompare);
}

void TrainingResultsWidget::removeComparisonResult(const QString &runNameToCompare) {
    deleteResultTab(runNameToCompare);
    emit sig_comparison_unloadAccuracyData(&*m_topAccuraciesView, &*m_topAccuraciesGraphics, runNameToCompare);
}

void TrainingResultsWidget::slot_normal_requestTopAccuraciesGraphics(GenericGraphicsView *receiver) {
    //Forward signal
    emit sig_normal_requestTopAccuraciesGraphics(receiver, &*m_topAccuraciesGraphics);
    //Graphics generation was requested; allow saving result
    m_topAccuraciesView->setSaved(false);
}

void TrainingResultsWidget::retranslateUi() {
    int index = getTabWidget()->indexOf(&*m_topAccuraciesView);
    getTabWidget()->setTabText(index, tr("Top Accuracies"));

    GenericComparisonWidget::retranslateUi();
}

void TrainingResultsWidget::saveResult(GenericGraphicsView *view) {
    if (view == &*m_topAccuraciesView)
            emit sig_save_TopAccuracies(&*m_topAccuraciesGraphics);
    else
            emit sig_save_TrainingResult(m_mapResultsByTab[view]);

    //Set result as saved, disables save button
    view->setSaved(true);
}

