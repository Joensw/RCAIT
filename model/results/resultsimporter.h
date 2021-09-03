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
    ResultsImporter();

    void updateResultFolderPaths();

public slots:

    //Top Accuracies slots
    void slot_comparison_loadAccuracyData(TopAccuraciesView *view, TopAccuraciesGraphics *graphics,
                                          const QString &runNameToCompare);

    static void slot_comparison_unloadAccuracyData(TopAccuraciesView *view, TopAccuraciesGraphics *graphics,
                                            const QString &runNameToCompare);

    //Classification result slots
    void slot_comparison_loadClassificationResultData(ClassificationResultView *view,
                                                      const QString &runNameToCompare);

    void slot_comparison_loadClassificationResultGraphics(GenericGraphicsView *receiver,
                                                          const QString &runNameToCompare);

    //Training result slots
    void slot_comparison_loadTrainingResultData(TrainingResultView *view, const QString &runNameToCompare);

    void slot_comparison_loadTrainingResultGraphics(GenericGraphicsView *receiver, const QString &runNameToCompare);

private:
    ProjectManager *m_projectManager;
    QString m_trainingResultsDir;
    QString m_classificationResultsDir;

    static QString getResultDataPath(const QString &resultNameTemplate, const QString &baseDir,
                                     const QString &identifier);

    static void
    loadGraphicsInView(GenericGraphicsView *receiver, const QString &resultsFolder, const QString &baseDir);

    [[nodiscard]] static QJsonObject readJSON(const QString &filepath);

    static void passResultGraphics(GenericGraphicsView *receiver, const QFileInfo &file, int type);

signals:

    void sig_normal_loadTrainingResultData(TrainingResultView *view, TrainingResult *result);

    void sig_normal_loadClassificationResultData(ClassificationResultView *view, ClassificationResult *result);
};

#endif // RESULTIMPORTER_H
