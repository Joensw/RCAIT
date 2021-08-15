#include "trainingresultswidget.h"

TrainingResultsWidget::TrainingResultsWidget(QWidget *parent)
        : GenericComparisonWidget(parent) {

    //Top Accuracies Tab configuration
    configure_topAccuraciesTab();
    connect(m_topAccuraciesView, &TopAccuraciesView::sig_normal_requestTopAccuraciesGraphics, this,
            &TrainingResultsWidget::slot_normal_requestTopAccuraciesGraphics);
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
    emit sig_comparison_loadAccuracyData(m_topAccuraciesView, m_topAccuraciesGraphics, runNameToCompare);
}

void TrainingResultsWidget::removeComparisonResult(const QString &runNameToCompare) {
    deleteResultTab(runNameToCompare);
    emit sig_comparison_unloadAccuracyData(m_topAccuraciesView, m_topAccuraciesGraphics, runNameToCompare);
}

void TrainingResultsWidget::configure_topAccuraciesTab() {
    const auto icon = QIcon(":/Resources/TabIcons/Filled/Results_Accuracy_Tab_Icon.svg");
    m_topAccuraciesView = new TopAccuraciesView(m_tabWidget);

    m_tabWidget->insertTab(0, m_topAccuraciesView, icon, QString());
}

void TrainingResultsWidget::slot_normal_requestTopAccuraciesGraphics(AbstractGraphicsView *receiver) {
    //Forward signal
    emit sig_normal_requestTopAccuraciesGraphics(receiver, m_topAccuraciesGraphics);
}

void TrainingResultsWidget::retranslateUi() {
    int index = m_tabWidget->indexOf(m_topAccuraciesView);
    m_tabWidget->setTabText(index, tr("Top Accuracies"));

    GenericComparisonWidget::retranslateUi();
}

void TrainingResultsWidget::saveResult(AbstractGraphicsView *view) {
    if (view == m_topAccuraciesView)
            emit sig_save_TopAccuracies(m_topAccuraciesGraphics);
    else
            emit sig_save_TrainingResult(m_mapResultsByTab[view]);
}

void TrainingResultsWidget::updateResultFolderPath(const QString &newDirPath) {
    GenericComparisonWidget::updateResultFolderPath(newDirPath);

    auto& pm = ProjectManager::getInstance();
    delete m_topAccuraciesGraphics;
    m_topAccuraciesGraphics = new TopAccuraciesGraphics(pm.getProjectTempDir());
}

