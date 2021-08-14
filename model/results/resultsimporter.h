#ifndef RESULTIMPORTER_H
#define RESULTIMPORTER_H

#include <QRegularExpression>
#include <projectmanager.h>
#include <QJsonParseError>
#include <QJsonDocument>
#include <topaccuraciesview.h>
#include <trainingresultview.h>
#include <classificationresultview.h>
#include "topaccuraciesgraphics.h"
#include "resultsprocessor.h"

class ResultsImporter : public QObject {
Q_OBJECT

public:
    void updateResultFolderPaths();

public slots:

    //Top Accuracies slots
    void slot_comparison_loadAccuracyData(TopAccuraciesView *view, TopAccuraciesGraphics *graphics,
                                          const QString &runNameToCompare);

    void slot_comparison_unloadAccuracyData(TopAccuraciesView *view, TopAccuraciesGraphics *graphics,
                                            const QString &runNameToCompare);

    //Classification result slots
    void slot_comparison_loadClassificationResultData(ClassificationResultView *view,
                                                      const QString &runNameToCompare);

    void slot_comparison_loadClassificationResultGraphics(AbstractGraphicsView *receiver,
                                                          const QString &runNameToCompare);

    //Training result slots
    void slot_comparison_loadTrainingResultData(TrainingResultView *view, const QString &runNameToCompare);

    void slot_comparison_loadTrainingResultGraphics(AbstractGraphicsView *receiver, const QString &runNameToCompare);

private:
    QString m_trainingResultsDir;
    QString m_classificationResultsDir;

    static QString getResultDataPath(const QString &resultNameTemplate, const QString &baseDir,
                                     const QString &identifier);

    static void
    loadGraphicsInView(AbstractGraphicsView *receiver, const QString &resultsFolder, const QString &baseDir);

    [[nodiscard]] static QJsonObject readJSON(const QString &filepath);

signals:

    void sig_normal_loadTrainingResultData(TrainingResultView *view, TrainingResult *result);

    void sig_normal_loadClassificationResultData(ClassificationResultView *view, ClassificationResult *result);

};

#endif // RESULTIMPORTER_H
