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

/**
 * @brief The TrainingResultWidget is used for displaying and comparing training results.
 */
class TrainingResultsWidget : public GenericComparisonWidget {
Q_OBJECT

public:
    /**
     * @brief Constructs a TrainingResultsWidget
     * @param parent QWidget parent object (optional)
     */
    explicit TrainingResultsWidget(QWidget *parent = nullptr);

    /**
     * @brief Destructor for this class.
     */
    ~TrainingResultsWidget() override = default;

    /**
     * @brief Adds a new training result
     * @param result result to be added
     */
    void addTrainingResult(TrainingResult *result);

    /**
     * @brief Updates the folder path to check for results to compare.
     * @param newDirPath path to new directory
     */
    void updateResultFolderPath(const QString &newDirPath) override;

private:
    static constexpr auto TOP_ACCURACIES_TAB_INDEX = 0;
    static constexpr auto TOP_ACCURACIES_TAB_ICON = ":/TabIcons/Filled/Results_Accuracy_Tab_Icon.svg";
    static constexpr auto TOP_ACCURACIES_TAB_NAME = QT_TR_NOOP("Top Accuracies");

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

    /**
     * @brief Signal is emitted when a result tab was created (for comparison) and data is requested.
     * @param view tab to be filled with data
     * @param runNameToCompare name of the result
     */
    void sig_comparison_loadTrainingResultData(TrainingResultView *view, const QString &runNameToCompare);

    /**
     * @brief Signal is emitted when a result tab was created (for comparison) and graphics are requested.
     * @param view tab that will display the graphics
     * @param runNameToCompare name of the result
     */
    void sig_comparison_loadTrainingResultGraphics(GenericGraphicsView *receiver, const QString &runNameToCompare);

    /**
     * @brief Signal is emitted when a result tab is added and data is requested.
     * @param view top accuracies tab to be filled with data
     * @param graphics contains the relevant data for parsing
     */
    void sig_comparison_loadAccuracyData(TopAccuraciesView *view, TopAccuraciesGraphics *graphics,
                                         const QString &runNameToCompare);

    /**
     * @brief Signal is emitted when a result tab is removed and data is requested.
     * @param view top accuracies view to update
     * @param graphics graphics to remove data from
     * @param runNameToCompare identifier to identify data
     */
    void sig_comparison_unloadAccuracyData(TopAccuraciesView *view, TopAccuraciesGraphics *graphics,
                                           const QString &runNameToCompare);

    /**
     * @brief Signal is emitted when a result tab was created (after a training) and data is requested.
     * @param view tab to be filled with data
     * @param result contains the relevant data for parsing
     */
    void sig_normal_loadTrainingResultData(TrainingResultView *view, TrainingResult *result);

    /**
     * @brief Signal is emitted when a result tab was created (after a training) and graphics are requested.
     * @param receiver tab that will display the graphics
     * @param result result that contains the relevant data
     */
    void sig_normal_generateTrainingResultGraphics(GenericGraphicsView *receiver, TrainingResult *result);


    /**
     * @brief Forwarded signal.
     * @param receiver top accuracies tab that will display the graphics
     * @param graphics object to trigger generation of the graphics on
     */
    void sig_normal_requestTopAccuraciesGraphics(TopAccuraciesView *receiver,
                                                 QSharedPointer<TopAccuraciesGraphics> graphics);

    /**
     * @brief Signal is emitted when a top accuracies tab is saved.
     * @param graphics graphics to be saved
     * @param success bool to report success state back to the view component
     */
    void sig_save_TopAccuracies(TopAccuraciesGraphics *graphics, bool &success);

    /**
     * @brief Signal is emitted when a training result tab is saved.
     * @param result result to be saved
     * @param success bool to report success state back to the view component
     */
    void sig_save_TrainingResult(TrainingResult *result, bool &success);

private slots:

    void slot_normal_requestTopAccuraciesGraphics(TopAccuraciesView *receiver);

};

#endif // TRAININGRESULTSWIDGET_H
