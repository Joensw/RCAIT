#ifndef RESULTEXPORTER_H
#define RESULTEXPORTER_H

#include <QString>
#include <QJsonObject>
#include <trainingresult.h>
#include <classificationresult.h>
#include <QJsonDocument>
#include <QFile>
#include <projectmanager.h>
#include <mapadapt.h>
#include <QJsonArray>
#include "topaccuraciesgraphics.h"
#include "resultsprocessor.h"

class ResultsExporter : public QObject {
Q_OBJECT

public:
    void updateResultFolderPaths();

public slots:

    void slot_save_TopAccuracies(TopAccuraciesGraphics *graphics);

    void slot_save_TrainingResult(TrainingResult *result);

    void slot_save_ClassificationResult(ClassificationResult *result);

private:
    QString m_trainingResultsDir;
    QString m_classificationResultsDir;

    static QDir createResultDir(const QString &baseDir, const QString &identifier);

    static void writeJSON(const QJsonObject &jsonObject, const QString &filepath);

    static void moveFile(const QString &oldFilePath, const QString &newFilePath) ;
};

#endif // RESULTEXPORTER_H
