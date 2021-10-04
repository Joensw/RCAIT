#include "trainingresultswidget.h"

TrainingResultsWidget::TrainingResultsWidget(QWidget *parent)
        : GenericComparisonWidget(parent),
          m_projectManager(&ProjectManager::getInstance()) {

    //Set up top accuracies tab
    configure_topAccuraciesTab();
}

void TrainingResultsWidget::configure_topAccuraciesTab() {
    const auto icon = QIcon(TOP_ACCURACIES_TAB_ICON);
    auto tempDir = m_projectManager->getProjectImageTempDir();

    //Cleanup old stuff
    getTabWidget()->removeTab(TOP_ACCURACIES_TAB_INDEX);
    //Old pointer will go out of scope after leaving this method and gets auto-deleted
    m_topAccuraciesView.reset(new TopAccuraciesView(this), &QObject::deleteLater);
    m_topAccuraciesGraphics.reset(new TopAccuraciesGraphics(tempDir), &QObject::deleteLater);

    //Connect signals and slots
    connect(&*m_topAccuraciesView, &TopAccuraciesView::sig_normal_requestTopAccuraciesGraphics, this,
            &TrainingResultsWidget::slot_normal_requestTopAccuraciesGraphics);

    //Configure tab
    getTabWidget()->insertTab(TOP_ACCURACIES_TAB_INDEX, &*m_topAccuraciesView, icon, QString());
    //Top Accuracies Tab cannot be saved in initial (= empty) state
    m_topAccuraciesView->setSaved(true);

    //Update UI to show changes
    retranslateUi();
}

void TrainingResultsWidget::updateResultFolderPath(const QString &newDirPath) {
    GenericComparisonWidget::updateResultFolderPath(newDirPath);

    configure_topAccuraciesTab();
}

void TrainingResultsWidget::addTrainingResult(const QPointer<TrainingResult> &result) {
    auto tab = createResultTab<TrainingResultView>(result->getIdentifier());
    m_mapResultsByTab[tab] = result;
    emit sig_normal_generateTrainingResultGraphics(tab, result);
    emit sig_normal_loadTrainingResultData(tab, result);
    emit sig_normal_loadAccuracyData(&*m_topAccuraciesView, &*m_topAccuraciesGraphics, result);
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

void TrainingResultsWidget::slot_normal_requestTopAccuraciesGraphics(TopAccuraciesView *receiver) {
    //Forward signal
    emit sig_normal_requestTopAccuraciesGraphics(receiver, m_topAccuraciesGraphics);
}

void TrainingResultsWidget::saveResult(GenericGraphicsView *view) {
    //Keeps user from clicking the save button multiple times
    view->setSaved(true);

    bool successful = false;
    if (view == &*m_topAccuraciesView)
            emit sig_save_TopAccuracies(&*m_topAccuraciesGraphics, successful);
    else
            emit sig_save_TrainingResult(m_mapResultsByTab[view], successful);

    //Set result as saved iff successful
    view->setSaved(successful);
    if (successful) configure_comparisonMenu();
}

void TrainingResultsWidget::retranslateUi() {
    int index = getTabWidget()->indexOf(&*m_topAccuraciesView);
    getTabWidget()->setTabText(index, tr(TOP_ACCURACIES_TAB_NAME));
    m_topAccuraciesView->setName(tr(TOP_ACCURACIES_TAB_NAME));

    GenericComparisonWidget::retranslateUi();
}

