#include <projectmanager.h>
#include "classificationresultswidget.h"

ClassificationResultsWidget::ClassificationResultsWidget(QWidget *parent) :
        GenericComparisonWidget(parent) {

    //TODO Replace dummy (without it, comparison menu won't appear)
    createResultTab<ClassificationResultView>("DUMMY");
}

void ClassificationResultsWidget::addClassificationResult(ClassificationResult *result) {
    auto tab = createResultTab<ClassificationResultView>(result->getIdentifier());
    m_mapResultsByTab[tab] = result;
    emit sig_normal_loadClassificationResultData(tab, result);
    emit sig_normal_generateClassificationResultGraphics(tab, result);
}

void ClassificationResultsWidget::saveResult(AbstractGraphicsView *view) {
    emit sig_save_ClassificationResult(m_mapResultsByTab[view]);
}

void ClassificationResultsWidget::addComparisonResult(const QString &runNameToCompare) {
    auto tab = createResultTab<ClassificationResultView>(runNameToCompare);
    //TODO Move to slot
    tab->setSaved(true);
    emit sig_comparison_loadClassificationResultData(tab, runNameToCompare);
    emit sig_comparison_loadClassificationResultGraphics(tab, runNameToCompare);
}

void ClassificationResultsWidget::removeComparisonResult(const QString &runNameToCompare) {
    deleteResultTab(runNameToCompare);
}