#ifndef RESULTSPROCESSOR_H
#define RESULTSPROCESSOR_H

#include <QString>
#include <QMap>
#include <trainingresultview.h>
#include <topaccuraciesview.h>
#include <classificationresultview.h>
#include <topaccuraciesgraphics.h>
#include <classificationgraphics.h>
#include <trainingresult.h>
#include <classificationresult.h>
#include <projectmanager.h>
#include <ce_string.h>

/**
 * @brief File name template for training results.\n
 * This naming structure is <b>guaranteed</b> to be the same for importing and exporting!
 */
static constexpr CE_String TRAINING_JSON = "training_%1.json";
/**
 * @brief File name template for classification results.\n
 * This naming structure is  <b>guaranteed</b> to be the same for importing and exporting!
 */
static constexpr CE_String CLASSIFICATION_JSON = "classification_%1.json";

/**
 * @brief This enum contains all types of supported graphics.
 * New result types can be inserted here,
 * along with the specification of how to import/process/export those results.
 */
enum GraphicsType {
    CLASSIFICATION,
    ACCURACYCURVE,
    CONFUSIONMATRIX,
    TOPACCURACIES,
    $GRAPHICSTYPES_COUNT
};

/**
 * @brief Regex for every result graphics file.
 */
static std::array<QRegularExpression, $GRAPHICSTYPES_COUNT> GRAPHICSTYPE2REGEX = {
        QRegularExpression("classification_(.*)\\.(svg|png)$"),
        QRegularExpression("accuracycurve_(.*)\\.(svg|png)$"),
        QRegularExpression("confusionmatrix_(.*)\\.(svg|png)$"),
        QRegularExpression("topaccuracies\\.(svg|png)$")
};

/**
 * @brief The <code>ResultsProcessor</code> prepares the data from the data management classes
 * so it can be used in display components
 */
class ResultsProcessor : public QObject {
Q_OBJECT
public:
    /**
     * @brief Default constructor.
     */
    ResultsProcessor() = default;

public slots:

    //Top Accuracies slots
    /**
     * @brief Generates and loads a TopAccuraciesGraphics into a TopAccuraciesView
     * @param receiver TopAccuraciesView to show the visualisation
     * @param graphics pointer to the graphics object to be visualised
     */
    void slot_normal_generateTopAccuraciesGraphics(TopAccuraciesView *receiver,
                                                   const QSharedPointer<TopAccuraciesGraphics> &graphics);

    //Classification result slots
    /**
     * @brief Loads the data of a ClassificationResult into a ClassificationResultView
     * @info Data and graphics are loaded separately so that you can specify
     * two different providers and the program remains extensible.
     * @param view ClassificationResultView to show the result
     * @param result ClassificationResult to be displayed
     */
    static void slot_normal_loadClassificationResultData(ClassificationResultView *view,
                                                         const QSharedPointer<ClassificationResult> &result);

    /**
     * @brief Generates and loads the graphics of a ClassificationResult into a ClassificationResultView
     * @info Data and graphics are loaded separately so that you can specify
     * two different providers and the program remains extensible.
     * @param receiver result tab to show the graphics
     * @param result ClassificationResult to be displayed
     */
    void slot_normal_generateClassificationResultGraphics(GenericGraphicsView *receiver,
                                                          const QSharedPointer<ClassificationResult> &result);

    //Training result slots
    /**
     * @brief Loads the data of a TrainingResult into a TrainingResultView
     * @info Data and graphics are loaded separately so that you can specify
     * two different providers and the program remains extensible.
     * @param view TrainingResultView to show the result
     * @param result TrainingResult to be displayed
     */
    static void
    slot_normal_loadTrainingResultData(TrainingResultView *view, const QSharedPointer<TrainingResult> &result);

    /**
     * @brief Generates and loads the graphics of a TrainingResult into a TrainingResultView
     * @info Data and graphics are loaded separately so that you can specify
     * two different providers and the program remains extensible.
     * @param receiver result tab to show the graphics
     * @param result TrainingResult to be displayed
     */
    void slot_normal_generateTrainingResultGraphics(GenericGraphicsView *receiver,
                                                    const QSharedPointer<TrainingResult> &result);

private:
    QMultiMap<GenericGraphicsView *, QSharedPointer<GenericResultGraphics>> m_mapGraphicsByReceiver;

    /**
     * @brief Manages a list of all graphics to generate for a particular result
     * and triggers their generation
     * @param receiver result tab to show the graphics
     * @param graphicsList list of graphics to schedule for generation
     */
    void addGraphicsGenerationJob(GenericGraphicsView *receiver,
                                  const QList<QSharedPointer<GenericResultGraphics>> &graphicsList);

private slots:

    /**
     * @brief Called after graphics generation.
     * Counts up if there are more graphics of the same result
     * and updates receiver state if necessary
     * @param receiver result tab to show the graphics
     * @param graphics graphics that was generated
     */
    void slot_graphicsGenerated(GenericGraphicsView *receiver, const QSharedPointer<GenericResultGraphics> &graphics);
};

#endif // RESULTSPROCESSOR_H
