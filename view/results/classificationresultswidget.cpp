#include <projectmanager.h>
#include "classificationresultswidget.h"

ClassificationResultsWidget::ClassificationResultsWidget(QWidget *parent) :
        GenericComparisonWidget(parent) {

    //TODO Replace dummy (without it, comparison menu won't appear)
    createResultTab("DUMMY");
}

ClassificationResultView *ClassificationResultsWidget::createResultTab(const QString &tabName) {
    auto *tab = new ClassificationResultView(this);
    m_tabWidget->addTab(tab, tabName);
    m_mapTabsByName[tabName] = tab;

    return tab;
}

void ClassificationResultsWidget::addClassificationResult(ClassificationResult *result) {
    auto tab = createResultTab(result->getIdentifier());
    emit sig_normal_loadClassificationData(tab, result);
    emit sig_normal_generateClassificationResultGraphics(tab, result);
}

void ClassificationResultsWidget::addComparisonResult(const QString &runNameToCompare) {
    auto tab = createResultTab(runNameToCompare);
    //TODO Move to slot
    tab->setSaved(true);
    emit sig_comparison_loadClassificationResultData(runNameToCompare, tab);
    emit sig_comparison_loadClassificationResultGraphics(runNameToCompare, tab);
}

void ClassificationResultsWidget::removeComparisonResult(const QString &runNameToCompare) {
    deleteResultTab(runNameToCompare);
}