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

class ResultsExporter : public QObject {
Q_OBJECT

public:
    ResultsExporter();

    void updateResultFolderPaths();

public slots:

    void slot_save_TopAccuracies(TopAccuraciesGraphics *graphics, bool &success = SAVED);

    void slot_save_TrainingResult(TrainingResult *result, bool &success = SAVED);

    void slot_save_ClassificationResult(ClassificationResult *result, bool &success = SAVED);

private:
    //Dummy variable to achieve optional parameters
    static bool SAVED;

    ProjectManager *m_projectManager;
    QString m_trainingResultsDir;
    QString m_classificationResultsDir;

    static QDir createResultDir(const QString &baseDir, const QString &identifier);

    static bool writeJSON(const QJsonObject &jsonObject, const QString &filepath);

    static bool saveFile(const QString &oldFilePath, const QString &newFilePath);

    static QJsonObject
    trainingResult2JSON(const TrainingResult *result);

    static QJsonObject
    classificationResult2JSON(const ClassificationResult *result);

    template<typename T>
    static QJsonArray QJsonArray_fromAnyList(const QList<T> &list) {
        QJsonArray JSONArray;

        for (const auto &value: list)
            JSONArray << value;

        return JSONArray;
    }
};

#endif // RESULTSEXPORTER_H
