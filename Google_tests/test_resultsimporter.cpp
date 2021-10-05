#include <QDir>
#include <gtest/gtest.h>
#include <QApplication>
#include "resultsimporter.h"
#include "trainingresultview.h"
#include "trainingresultswidget.h"
#include <QtTest/QSignalSpy>
#include "resultsexporter.h"


class ResultsImporterTest : public testing::Test {
protected:


    static void SetUpTestSuite() {
    }

    static void TearDownTestSuite() {
    }

    void SetUp() override {

        classiResultsDir = QDir::current().path() + "/classresults";
        resultsDir = QDir::current().path() + "/results";

    }

    void TearDown() override {

    }


    QString resultsDir;
    QString classiResultsDir;
    QString tempProjectsDir = "./projectsForTests";
    QString testProjectName = "testProject";
    QString f = "training_run.json";

    void copyPath(QString src, QString dst) {
        QDir dir(src);
        if (!dir.exists())
            return;

        for (const QString &d: dir.entryList(QDir::Dirs | QDir::NoDotAndDotDot)) {
            QString dst_path = dst + QDir::separator() + d;
            dir.mkpath(dst_path);
            copyPath(src + QDir::separator() + d, dst_path);
        }

        for (const QString &file: dir.entryList(QDir::Files)) {
            QFile::copy(src + QDir::separator() + file, dst + QDir::separator() + file);
        }
    }


};


TEST_F(ResultsImporterTest, testCallMethods) {

    int argc = 1;
    char *argv[1] = {new char('a')};
    QApplication a(argc, argv);

    ResultsExporter resultsExporter;
    ResultsImporter resultsImporter;
    ProjectManager *pm = &ProjectManager::getInstance();
    pm->setProjectsDirectory(tempProjectsDir);
    QString error;
    bool out = pm->createNewProject(testProjectName, error);


    pm->loadProject(testProjectName);
    QString TrainingResultsDir = pm->getTrainingResultsDir();
    QDir trResDir(TrainingResultsDir);

    QString classResultsDir = pm->getClassificationResultsDir();
    QDir clResDir(classResultsDir);

    copyPath(resultsDir, trResDir.absolutePath());
    copyPath(classiResultsDir, clResDir.absolutePath());

    //EXPECT_TRUE(QFile::copy(fDir,tarDir));
    resultsImporter.updateResultFolderPaths();
    resultsExporter.updateResultFolderPaths();

    auto savableResultsWidget = QScopedPointer<TrainingResultsWidget>(new TrainingResultsWidget);
    auto trainingResultView = QScopedPointer<TrainingResultView>(new TrainingResultView(&*savableResultsWidget));

    auto savableResultsWidget2 = QScopedPointer<TrainingResultsWidget>(new TrainingResultsWidget);
    auto classificationResultView = QScopedPointer<ClassificationResultView>(
            new ClassificationResultView(&*savableResultsWidget2));

    qRegisterMetaType<TrainingResult>();
    qRegisterMetaType<ClassificationResult>();
    //qRegisterMetaType<TrainingResultView>();
    QSignalSpy spy(&resultsImporter, &ResultsImporter::sig_normal_loadTrainingResultData);
    QSignalSpy spy2(&resultsImporter, &ResultsImporter::sig_normal_loadClassificationResultData);
    resultsImporter.slot_comparison_loadTrainingResultData(&*trainingResultView, "run");
    resultsImporter.slot_comparison_loadClassificationResultData(&*classificationResultView, "fun");

    spy2.wait(1000);
    spy.wait(1000);
    //QList<QVariant> arguments = spy.takeFirst();
    //TrainingResultView resultView = qvariant_cast<TrainingResultView>(spy.at(0).at(0));
    auto result = spy.at(0).at(1).value<QPointer<TrainingResult>>();
    auto result2 = spy2.at(0).at(1).value<QPointer<ClassificationResult>>();
    std::pair<double, double> p1{75.0, 0.0};
    std::pair<double, double> p2{0.0, 0.0};
    EXPECT_EQ(result->getAccuracyCurveData().value(100), p1);
    EXPECT_EQ(result->getAccuracyCurveData().value(200), p2);

    EXPECT_EQ(result->getClassLabels().at(0), "Flugzeug");
    EXPECT_EQ(result->getClassLabels().at(1), "Zug");

    EXPECT_EQ(result->getConfusionMatrixValues().at(0), 9);
    EXPECT_EQ(result->getConfusionMatrixValues().at(1), 5);
    EXPECT_EQ(result->getConfusionMatrixValues().at(2), 0);
    EXPECT_EQ(result->getConfusionMatrixValues().at(3), 14);

    EXPECT_EQ(result->getMostMisclassifiedImages().at(0), "path/one/");
    EXPECT_EQ(result->getMostMisclassifiedImages().at(1), "path/two/");
    EXPECT_EQ(result->getMostMisclassifiedImages().at(2), "path/three/");

    EXPECT_DOUBLE_EQ(result->getTop1Accuracy(), 82.142857142857139);

    EXPECT_DOUBLE_EQ(result->getTop5Accuracy(), 100.0);


    EXPECT_DOUBLE_EQ(result2->getClassificationData().value(
            "/home/ies/ott/pseVNC/ProjektDirectory/DataAugTest/data/validation/bank/bank_53.jpg").at(0),
                     0.90369337797164917);
    EXPECT_DOUBLE_EQ(result2->getClassificationData().value(
            "/home/ies/ott/pseVNC/ProjektDirectory/DataAugTest/data/validation/bank/bank_53.jpg").at(1),
                     0.087613902986049652);
    EXPECT_DOUBLE_EQ(result2->getClassificationData().value(
            "/home/ies/ott/pseVNC/ProjektDirectory/DataAugTest/data/validation/bank/bank_53.jpg").at(2),
                     0.0086927767843008041);

    EXPECT_EQ(result2->getLabels().at(0), "bank");
    EXPECT_EQ(result2->getLabels().at(1), "boat");
    EXPECT_EQ(result2->getLabels().at(2), "bread");

    //test resultsexporter
    bool success;
    resultsExporter.slot_save_TrainingResult(result, success);
    resultsExporter.slot_save_ClassificationResult(result2, success);


    //TearDown
    QDir projectsDir(tempProjectsDir);
    projectsDir.removeRecursively();
    QApplication::exit();
    EXPECT_TRUE(true);
}
