#ifndef TRAININGRESULTSWIDGET_H
#define TRAININGRESULTSWIDGET_H

#include <QWidget>
#include <QMenu>
#include <QPushButton>
#include <QRandomGenerator>
#include <accuracycurve.h>
#include <confusionmatrix.h>
#include <projectmanager.h>
#include <topaccuraciesgraphics.h>
#include "topaccuraciesview.h"
#include "trainingresultview.h"
#include "genericcomparisonwidget.h"

class TrainingResultsWidget : public GenericComparisonWidget {
Q_OBJECT

public:
    explicit TrainingResultsWidget(QWidget *parent = nullptr);

    ~TrainingResultsWidget() override = default;

    void addTrainingResult(TrainingResult *result);

private:
    TopAccuraciesView *m_topAccuraciesView;
    TopAccuraciesGraphics *m_topAccuraciesGraphics;

    void addComparisonResult(const QString &runNameToCompare) override;

    void removeComparisonResult(const QString &runNameToCompare) override;

    void configure_topAccuraciesTab();

    TrainingResultView *createResultTab(const QString &tabName) override;

signals:

    void sig_comparison_loadTrainingResultData(TrainingResultView *view, const QString &runNameToCompare);

    void sig_comparison_loadTrainingResultGraphics(AbstractGraphicsView *receiver, const QString &runNameToCompare);

    void sig_comparison_loadAccuracyData(TopAccuraciesView *view, TopAccuraciesGraphics *graphics,
                                         const QString &runNameToCompare);

    void sig_comparison_unloadAccuracyData(TopAccuraciesView *view, TopAccuraciesGraphics *graphics,
                                           const QString &runNameToCompare);

    void sig_normal_generateTrainingResultGraphics(AbstractGraphicsView *receiver, TrainingResult *result);

    void sig_normal_loadTrainingResultData(TrainingResultView *view, TrainingResult *result);

    void sig_normal_requestTopAccuraciesGraphics(AbstractGraphicsView *receiver, TopAccuraciesGraphics *graphics);

private slots:

    void slot_normal_requestTopAccuraciesGraphics(AbstractGraphicsView *receiver);
};

#endif // TRAININGRESULTSWIDGET_H
