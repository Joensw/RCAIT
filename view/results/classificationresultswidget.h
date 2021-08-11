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

    ~ClassificationResultsWidget() = default;

    void addClassificationResult(ClassificationResult *result);

private:
    ClassificationResultView *createResultTab(const QString &tabName) override;

    void addComparisonResult(const QString &runNameToCompare) override;

    void removeComparisonResult(const QString &runNameToCompare) override;

signals:

    void sig_comparison_loadClassificationResultData(ClassificationResultView *view, const QString &runNameToCompare);

    void
    sig_comparison_loadClassificationResultGraphics(ClassificationResultView *view, const QString &runNameToCompare);

    void sig_normal_loadClassificationResultData(ClassificationResultView *view, ClassificationResult *result);

    void sig_normal_generateClassificationResultGraphics(AbstractGraphicsView *receiver, ClassificationResult *result);
};

#endif // CLASSIFICATIONRESULTSWIDGET_H
