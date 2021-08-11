#include "trainingresultswidget.h"

TrainingResultsWidget::TrainingResultsWidget(QWidget *parent)
        : GenericComparisonWidget(parent) {

    //Top Accuracies Tab configuration
    m_topAccuraciesGraphics = new TopAccuraciesGraphics("comparison");
    configure_topAccuraciesTab();
    connect(m_topAccuraciesView, &TopAccuraciesView::sig_normal_requestTopAccuraciesGraphics, this,
            &TrainingResultsWidget::slot_normal_requestTopAccuraciesGraphics);
}

void TrainingResultsWidget::addTrainingResult(TrainingResult *result) {
    auto tab = createResultTab(result->getIdentifier());
    emit sig_normal_generateTrainingResultGraphics(tab, result);
    emit sig_normal_loadTrainingResultData(tab, result);
}

void TrainingResultsWidget::addComparisonResult(const QString &runNameToCompare) {
    auto tab = createResultTab(runNameToCompare);
    //TODO move to slot
    tab->setSaved(true);
    emit sig_comparison_loadTrainingResultGraphics(tab, runNameToCompare);
    emit sig_comparison_loadTrainingResultData(tab, runNameToCompare);
    emit sig_comparison_loadAccuracyData(m_topAccuraciesView, m_topAccuraciesGraphics, runNameToCompare);
}

void TrainingResultsWidget::removeComparisonResult(const QString &runNameToCompare) {
    deleteResultTab(runNameToCompare);
    emit sig_comparison_unloadAccuracyData(m_topAccuraciesView, m_topAccuraciesGraphics, runNameToCompare);
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

void TrainingResultsWidget::slot_normal_requestTopAccuraciesGraphics(AbstractGraphicsView *receiver) {
    //Forward signal
    emit sig_normal_requestTopAccuraciesGraphics(receiver, m_topAccuraciesGraphics);
}
