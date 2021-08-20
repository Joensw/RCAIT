#include <projectmanager.h>
#include <QProxyStyle>
#include "classificationresultswidget.h"

ClassificationResultsWidget::ClassificationResultsWidget(QWidget *parent) :
        GenericComparisonWidget(parent) {

    //Placeholder for symmetry to 'Top Accuracies' Tab in TrainingResultsWidget
    configure_placeholderTab();
}

void ClassificationResultsWidget::configure_placeholderTab() {
    const auto icon = QIcon(":/Resources/TabIcons/Filled/Results_Accuracy_Tab_Icon.svg");
    auto placeholder = new GenericGraphicsView(this);
    m_tabWidget->insertTab(0, placeholder, icon, QString());
    m_tabWidget->setTabEnabled(0, false);
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
    emit sig_save_ClassificationResult(m_mapResultsByTab[view]);
}

void ClassificationResultsWidget::addComparisonResult(const QString &runNameToCompare) {
    auto tab = createResultTab<ClassificationResultView>(runNameToCompare);
    emit sig_comparison_loadClassificationResultData(tab, runNameToCompare);
    emit sig_comparison_loadClassificationResultGraphics(tab, runNameToCompare);
}

void ClassificationResultsWidget::removeComparisonResult(const QString &runNameToCompare) {
    deleteResultTab(runNameToCompare);
}