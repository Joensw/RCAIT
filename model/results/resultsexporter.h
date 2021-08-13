#ifndef RESULTEXPORTER_H
#define RESULTEXPORTER_H

#include <QString>
#include <QJsonObject>
#include <trainingresult.h>
#include <classificationresult.h>
#include "topaccuraciesgraphics.h"

class ResultsExporter : public QObject {
Q_OBJECT

public slots:

    void slot_save_TopAccuracies(TopAccuraciesGraphics *graphics);

    void slot_save_TrainingResult(TrainingResult *result);

    void slot_save_ClassificationResult(ClassificationResult *result);


    void updateResultFolderPaths();

private:
    QString m_resultsDir;
    QString m_trainingResultsDir;
    QString m_classificationResultsDir;

    static void writeJSON(const QJsonObject &jsonObject, const QString &filepath);


};

#endif // RESULTEXPORTER_H
