#include "trainingresultswidget.h"

TrainingResultsWidget::TrainingResultsWidget(QWidget *parent)
        : GenericComparisonWidget(parent) {

    configure_topAccuraciesTab();
}

void TrainingResultsWidget::addTrainingResult(TrainingResult *result) {
    auto tab = createResultTab(result->getIdentifier());
    emit sig_normal_generateTrainingResultGraphics(tab, result);
    emit sig_normal_loadTrainingResultData(tab, result);
}

TopAccuraciesView *TrainingResultsWidget::getTopAccuraciesView() {
    return m_topAccuraciesView;
}

void TrainingResultsWidget::addComparisonResult(const QString &runNameToCompare) {
    auto tab = createResultTab(runNameToCompare);
    //TODO move to slot
    tab->setSaved(true);
    emit sig_comparison_loadTrainingResultGraphics(tab, runNameToCompare);
    emit sig_comparison_loadTrainingResultData(tab,runNameToCompare);
    emit sig_comparison_loadAccuracyData(m_topAccuraciesView, runNameToCompare);
}

void TrainingResultsWidget::removeComparisonResult(const QString &runNameToCompare) {
    deleteResultTab(runNameToCompare);
    emit sig_comparison_unloadAccuracyData(m_topAccuraciesView, runNameToCompare);
}

void TrainingResultsWidget::configure_topAccuraciesTab() {
    const QString tabName = "Top Accuracies";
    const auto icon = QIcon(":/Resources/TabIcons/Filled/Results_Accuracy_Tab_Icon.svg");
    m_topAccuraciesView = new TopAccuraciesView(m_tabWidget);

    m_tabWidget->insertTab(0, m_topAccuraciesView, icon, tabName);
}

TrainingResultView *TrainingResultsWidget::createResultTab(const QString &tabName) {

    auto *tab = new TrainingResultView(this);
    m_tabWidget->addTab(tab, tabName);
    m_mapTabsByName[tabName] = tab;

    return tab;
}
