#include "classificationresultswidget.h"

ClassificationResultsWidget::ClassificationResultsWidget(QWidget *parent) :
        GenericComparisonWidget(parent) {

    //Placeholder for symmetry to 'Top Accuracies' Tab in TrainingResultsWidget
    configure_placeholderTab();
}

void ClassificationResultsWidget::configure_placeholderTab() {
    const auto icon = QIcon(PLACEHOLDER_TAB_ICON);
    auto placeholder = new GenericGraphicsView(this);
    getTabWidget()->insertTab(PLACEHOLDER_TAB_INDEX, placeholder, icon, QString());
    getTabWidget()->setTabEnabled(PLACEHOLDER_TAB_INDEX, false);
    //Placeholder cannot be saved
    placeholder->setSaved(true);
}

void ClassificationResultsWidget::addClassificationResult(ClassificationResult *result) {
    auto tab = createResultTab<ClassificationResultView>(result->getIdentifier());
    m_mapResultsByTab[tab] = result;
    emit sig_normal_loadClassificationResultData(tab, result);
    emit sig_normal_generateClassificationResultGraphics(tab, result);
}

void ClassificationResultsWidget::saveResult(GenericGraphicsView *view) {
    //Keeps user from clicking the save button multiple times
    view->setSaved(true);

    bool success;
    emit sig_save_ClassificationResult(m_mapResultsByTab[view], success);
    //Set result as saved iff successful
    view->setSaved(success);
}

void ClassificationResultsWidget::addComparisonResult(const QString &runNameToCompare) {
    auto tab = createResultTab<ClassificationResultView>(runNameToCompare);
    emit sig_comparison_loadClassificationResultData(tab, runNameToCompare);
    emit sig_comparison_loadClassificationResultGraphics(tab, runNameToCompare);
}

void ClassificationResultsWidget::removeComparisonResult(const QString &runNameToCompare) {
    deleteResultTab(runNameToCompare);
}
