#ifndef CLASSIFICATIONRESULTSWIDGET_H
#define CLASSIFICATIONRESULTSWIDGET_H

#include <QWidget>
#include <QPushButton>
#include <QMenu>
#include <classificationresult.h>
#include "classificationresultview.h"
#include "genericcomparisonwidget.h"

class ClassificationResultsWidget : public GenericComparisonWidget {
Q_OBJECT

public:
    explicit ClassificationResultsWidget(QWidget *parent = nullptr);

    ~ClassificationResultsWidget() override = default;

    void addClassificationResult(ClassificationResult *result);

private:
    static constexpr auto PLACEHOLDER_TAB_INDEX = 0;
    static constexpr auto PLACEHOLDER_TAB_ICON = ":/TabIcons/Filled/Results_Accuracy_Tab_Icon.svg";

    QMap<GenericGraphicsView *, ClassificationResult *> m_mapResultsByTab;

    void addComparisonResult(const QString &runNameToCompare) override;

    void removeComparisonResult(const QString &runNameToCompare) override;

    void saveResult(GenericGraphicsView *view) override;

    void configure_placeholderTab();

signals:

    void sig_comparison_loadClassificationResultData(ClassificationResultView *view, const QString &runNameToCompare);

    void
    sig_comparison_loadClassificationResultGraphics(ClassificationResultView *view, const QString &runNameToCompare);

    void sig_normal_loadClassificationResultData(ClassificationResultView *view, ClassificationResult *result);

    void sig_normal_generateClassificationResultGraphics(GenericGraphicsView *receiver, ClassificationResult *result);

    void sig_save_ClassificationResult(ClassificationResult *result, bool &success);

};

#endif // CLASSIFICATIONRESULTSWIDGET_H
