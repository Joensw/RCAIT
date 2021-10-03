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
#include <json_toolbox.h>

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
    void slot_save_TopAccuracies(const QSharedPointer<TopAccuraciesGraphics> &graphics, bool &success = SAVED) const;

    /**
     * @brief Saves a given training result.
     * @param result result to be saved
     * @param success bool to report success state back to the view component
     */
    void slot_save_TrainingResult(const QSharedPointer<TrainingResult> &result, bool &success = SAVED) const;

    /**
     * @brief Saves a given classification result.
     * @param result result to be saved
     * @param success bool to report success state back to the view component
     */
    void
    slot_save_ClassificationResult(const QSharedPointer<ClassificationResult> &result, bool &success = SAVED) const;

private:

    /**
     * @brief Dummy variable to achieve optional parameters
     */
    static inline bool SAVED = false;

    ProjectManager *m_projectManager;
    QString m_resultsDir;
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
     * @brief Moves all graphics from the results directory in their specific subfolder.
     * @param type type of graphics to save
     */
    bool saveGraphics(int type) const;

    /**
     * @brief Convert a TrainingResult into a QJsonObject
     * @param result result to be converted
     * @return filled QJsonObject
     */
    static QJsonObject
    trainingResult2JSON(const QSharedPointer<TrainingResult> &result);

    /**
     * @brief Convert a ClassificationResult into a QJsonObject
     * @param result result to be converted
     * @return filled QJsonObject
     */
    static QJsonObject
    classificationResult2JSON(const QSharedPointer<ClassificationResult> &result);

    bool graphicsTypeMultiplexer(int type, const QString &filePath, const QString &identifier) const;
};

#endif // RESULTSEXPORTER_H
