#ifndef RESULTSIMPORTER_H
#define RESULTSIMPORTER_H

#include <QRegularExpression>
#include <projectmanager.h>
#include <QJsonParseError>
#include <QJsonDocument>
#include <topaccuraciesview.h>
#include <trainingresultview.h>
#include <classificationresultview.h>
#include "topaccuraciesgraphics.h"
#include "resultsprocessor.h"

/**
 * @brief The <code>ResultsImporter</code> is used to import all types of specialised results
 * from JSON files and also imports result graphics.
 */
class ResultsImporter : public QObject {
Q_OBJECT

public:
    /**
     * @brief Constructs a ResultsExporter
     */
    ResultsImporter();

    /**
     * @brief Update results folder used to import results from
     */
    void updateResultFolderPaths();

signals:

    /**
     * @brief Emitted after TrainingResult Data was loaded
     * @param view result tab to load the result into
     * @param result imported result
     */
    void sig_normal_loadTrainingResultData(TrainingResultView *view, TrainingResult *result);

    /**
     * @brief Emitted after ClassificationResult Data was loaded
     * @param view result tab to load the result into
     * @param result imported result
     */
    void sig_normal_loadClassificationResultData(ClassificationResultView *view, ClassificationResult *result);

public slots:

    //Top Accuracies slots
    /**
     * @brief Import accuracy data to display in a TopAccuraciesView
     * @param view TopAccuraciesView to display the data in
     * @param graphics graphics to provide the data to
     * @param runNameToCompare identifier of the result to import
     */
    void slot_comparison_loadAccuracyData(TopAccuraciesView *view, TopAccuraciesGraphics *graphics,
                                          const QString &runNameToCompare);

    /**
     * @brief Unload accuracy data when a comparison result is now unselected
     * @param view TopAccuraciesView to update
     * @param graphics graphics to unload the data from
     * @param runNameToCompare result identifier to unload
     */
    static void slot_comparison_unloadAccuracyData(TopAccuraciesView *view, TopAccuraciesGraphics *graphics,
                                                   const QString &runNameToCompare);

    //Classification result slots
    /**
     * @brief Imports data of a given classification result by identifier
     * @param view ClassificationResultView to display the result
     * @param runNameToCompare identifier of the result to import
     */
    void slot_comparison_loadClassificationResultData(ClassificationResultView *view,
                                                      const QString &runNameToCompare);

    /**
     * @brief Imports graphics of a given classification result by identifier
     * @param receiver result tab to display the result
     * @param runNameToCompare identifier of the result to import
     */
    void slot_comparison_loadClassificationResultGraphics(GenericGraphicsView *receiver,
                                                          const QString &runNameToCompare);

    //Training result slots
    /**
     * @brief Imports data of a given training result by identifier
     * @param view TrainingResultView to display the result
     * @param runNameToCompare identifier of the result to import
     */
    void slot_comparison_loadTrainingResultData(TrainingResultView *view, const QString &runNameToCompare);

    /**
     * @brief Imports graphics of a given training result by identifier
     * @param receiver result tab to display the result
     * @param runNameToCompare identifier of the result to import
     */
    void slot_comparison_loadTrainingResultGraphics(GenericGraphicsView *receiver, const QString &runNameToCompare);

private:
    ProjectManager *m_projectManager;
    QString m_trainingResultsDir;
    QString m_classificationResultsDir;

    /**
     * @brief Get the path of a result data file (JSON), if existent.
     * @param resultNameTemplate name template to fill
     * @param baseDir contains result folders
     * @param identifier name of the particular results folder to lookup
     * @return path of the result data file, if existent
     */
    static QString getResultDataPath(const QString &resultNameTemplate, const QString &baseDir,
                                     const QString &identifier);

    /**
     * @brief Load graphics from a result folder and hand them to a result view
     * @param receiver result view to display the generated graphics
     * @param baseDir contains result folders
     * @param resultsFolder folder name identifier to lookup in baseDir
     */
    static void
    loadGraphicsInView(GenericGraphicsView *receiver, const QString &baseDir,
                       const QString &resultsFolder);

    /**
     * @brief Read a JSON file into a QJsonObject
     * @param filepath path of JSON file
     * @return QJsonObject containing the file data in a usable format
     */
    [[nodiscard]] static QJsonObject readJSON(const QString &filepath);

    /**
     * @brief Helper method. Pass result to the right method via multiplexer
     * @param receiver result view to display the generated graphics
     * @param file graphics file to be read and parsed
     * @param type internal type number for each result type
     */
    static void passResultGraphicsMultiplexer(GenericGraphicsView *receiver, const QFileInfo &file, int type);

    /**
     * @brief Read a QJsonArray into a list of arbitrary type
     * @tparam T desired type
     * @param json_array QJsonArray to be read
     * @return list of desired type
     */
    template<typename T>
    static QList<T> QJsonArray_toList(const QJsonArray &json_array) {
        QList<T> list;

        for (const auto &item: json_array) {
            Q_ASSERT(item.toVariant().canConvert<T>());
            list << qvariant_cast<T>(item.toVariant());
        }
        return list;
    }
};

#endif // RESULTSIMPORTER_H
