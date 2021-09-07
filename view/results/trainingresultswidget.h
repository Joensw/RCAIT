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

    void updateResultFolderPath(const QString &newDirPath) override;

private:
    static constexpr auto TOP_ACCURACIES_TAB_INDEX = 0;
    static constexpr auto TOP_ACCURACIES_TAB_ICON = ":/TabIcons/Filled/Results_Accuracy_Tab_Icon.svg";
    static constexpr auto TOP_ACCURACIES_TAB_NAME = "Top Accuracies";

    ProjectManager *m_projectManager;
    QScopedPointer<TopAccuraciesView> m_topAccuraciesView;
    QSharedPointer<TopAccuraciesGraphics> m_topAccuraciesGraphics;
    QMap<GenericGraphicsView *, TrainingResult *> m_mapResultsByTab;

    void addComparisonResult(const QString &runNameToCompare) override;

    void removeComparisonResult(const QString &runNameToCompare) override;

    void saveResult(GenericGraphicsView *view) override;

    void configure_topAccuraciesTab();

    void retranslateUi() override;

signals:

    void sig_comparison_loadTrainingResultData(TrainingResultView *view, const QString &runNameToCompare);

    void sig_comparison_loadTrainingResultGraphics(GenericGraphicsView *receiver, const QString &runNameToCompare);

    void sig_comparison_loadAccuracyData(TopAccuraciesView *view, TopAccuraciesGraphics *graphics,
                                         const QString &runNameToCompare);

    void sig_comparison_unloadAccuracyData(TopAccuraciesView *view, TopAccuraciesGraphics *graphics,
                                           const QString &runNameToCompare);

    void sig_normal_generateTrainingResultGraphics(GenericGraphicsView *receiver, TrainingResult *result);

    void sig_normal_loadTrainingResultData(TrainingResultView *view, TrainingResult *result);

    void sig_normal_requestTopAccuraciesGraphics(TopAccuraciesView *receiver,
                                                 QSharedPointer<TopAccuraciesGraphics> graphics);

    void sig_save_TopAccuracies(TopAccuraciesGraphics *graphics, bool& success);

    void sig_save_TrainingResult(TrainingResult *result, bool &success);

private slots:

    void slot_normal_requestTopAccuraciesGraphics(TopAccuraciesView *receiver);

};

#endif // TRAININGRESULTSWIDGET_H
