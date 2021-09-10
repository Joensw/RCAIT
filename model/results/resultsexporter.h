#ifndef RESULTSEXPORTER_H
#define RESULTSEXPORTER_H

#include <QString>
#include <QJsonObject>
#include <trainingresult.h>
#include <classificationresult.h>
#include <QJsonDocument>
#include <QFile>
#include <projectmanager.h>
#include <model/utilities/mapadapt.h>
#include <QJsonArray>
#include "topaccuraciesgraphics.h"
#include "resultsprocessor.h"

/**
 * @brief Dummy variable to achieve optional parameters
 */
static bool SAVED;

/**
 * @brief The <code>ResultsExporter</code> is used to export all types of specialised results
 * in JSON files and save result graphics.
 */
class ResultsExporter : public QObject {
Q_OBJECT

public:
    /**
     * @brief Constructs a ResultsExporter
     */
    ResultsExporter();

    /**
     * @brief Update results folder used as saving location
     */
    void updateResultFolderPaths();

public slots:

    /**
     * @brief Saves a given TopAccuraciesGraphics
     * @param graphics graphics to be saved
     * @param success bool to report success state back to the view component
     */
    void slot_save_TopAccuracies(TopAccuraciesGraphics *graphics, bool &success = SAVED);

    /**
     * @brief Saves a given training result.
     * @param result result to be saved
     * @param success bool to report success state back to the view component
     */
    void slot_save_TrainingResult(TrainingResult *result, bool &success = SAVED);

    /**
     * @brief Saves a given classification result.
     * @param result result to be saved
     * @param success bool to report success state back to the view component
     */
    void slot_save_ClassificationResult(ClassificationResult *result, bool &success = SAVED);

private:

    ProjectManager *m_projectManager;
    QString m_trainingResultsDir;
    QString m_classificationResultsDir;

    /**
     * @brief Create a folder for all files related to one result
     * @param baseDir folder to create subfolder in
     * @param identifier result identifier and subfolder name
     * @return QDir of the subfolder
     */
    static QDir createResultDir(const QString &baseDir, const QString &identifier);

    /**
     * @brief Write a QJsonObject into a JSON file
     * @param jsonObject object to write to file
     * @param filepath path to store JSON file
     * @return success state
     */
    static bool writeJSON(const QJsonObject &jsonObject, const QString &filepath);

    /**
     * @brief Saves a given file to another place, removes the original on success.
     * @param oldFilePath current file location
     * @param newFilePath desired file location
     * @return success state
     */
    static bool saveFile(const QString &oldFilePath, const QString &newFilePath);

    /**
     * @brief Convert a TrainingResult into a QJsonObject
     * @param result result to be converted
     * @return filled QJsonObject
     */
    static QJsonObject
    trainingResult2JSON(const TrainingResult *result);

    /**
     * @brief Convert a ClassificationResult into a QJsonObject
     * @param result result to be converted
     * @return filled QJsonObject
     */
    static QJsonObject
    classificationResult2JSON(const ClassificationResult *result);

    /**
     * @brief Read any type of QList and make it a QJsonArray
     * @tparam T arbitrary type
     * @param list list to be converted
     * @return QJsonArray containing the same elements
     */
    template<typename T>
    static QJsonArray QJsonArray_fromAnyList(const QList<T> &list) {
        QJsonArray JSONArray;

        for (const auto &value: list)
            JSONArray << value;

        return JSONArray;
    }
};

#endif // RESULTSEXPORTER_H
