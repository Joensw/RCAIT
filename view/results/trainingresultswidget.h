#ifndef TRAININGRESULTSWIDGET_H
#define TRAININGRESULTSWIDGET_H

#include <QWidget>
#include <QMenu>
#include <QPushButton>
#include <QRandomGenerator>
#include <accuracycurve.h>
#include <confusionmatrix.h>
#include <projectmanager.h>
#include "topaccuraciesview.h"
#include "trainingresultview.h"
#include "genericcomparisonwidget.h"

class TrainingResultsWidget : public GenericComparisonWidget {
Q_OBJECT

public:
    explicit TrainingResultsWidget(QWidget *parent = nullptr);

    ~TrainingResultsWidget() = default;

    void addTrainingResult(TrainingResult *result);

    TopAccuraciesView *getTopAccuraciesView();

private:
    TopAccuraciesView *m_topAccuraciesView;

    void addComparisonResult(const QString &runNameToCompare) override;

    void removeComparisonResult(const QString &runNameToCompare) override;

    void configure_topAccuraciesTab();

    TrainingResultView *createResultTab(const QString &tabName) override;

signals:

    void sig_comparison_loadTrainingResultData(TrainingResultView *view, const QString &runNameToCompare);

    void sig_comparison_loadTrainingResultGraphics(AbstractGraphicsView *receiver, const QString &runNameToCompare);

    void sig_comparison_loadAccuracyData(TopAccuraciesView *view, const QString &runNameToCompare);

    void sig_comparison_unloadAccuracyData(TopAccuraciesView *view, const QString &runNameToCompare);

    void sig_normal_generateTrainingResultGraphics(AbstractGraphicsView *receiver, TrainingResult *result);

    void sig_normal_loadTrainingResultData(TrainingResultView *view, TrainingResult *result);

};

#endif // TRAININGRESULTSWIDGET_H
