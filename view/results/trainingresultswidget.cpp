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
    auto tab = createResultTab<TrainingResultView>(result->getIdentifier());
    emit sig_normal_generateTrainingResultGraphics(tab, result);
    emit sig_normal_loadTrainingResultData(tab, result);
}

void TrainingResultsWidget::addComparisonResult(const QString &runNameToCompare) {
    auto tab = createResultTab<TrainingResultView>(runNameToCompare);
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

