#include <QDir>
#include <gtest/gtest.h>
#include <QApplication>
#include "resultsimporter.h"
#include "trainingresultview.h"
#include "trainingresultswidget.h"
#include <QWidget>
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


    void copyPath(QString src, QString dst)
    {
        QDir dir(src);
        if (! dir.exists())
            return;

        for (const QString &d: dir.entryList(QDir::Dirs | QDir::NoDotAndDotDot)) {
            QString dst_path = dst + QDir::separator() + d;
            dir.mkpath(dst_path);
            copyPath(src + QDir::separator() + d, dst_path);
        }

        for (const QString &f: dir.entryList(QDir::Files)) {
            QFile::copy(src + QDir::separator() + f, dst + QDir::separator() + f);
        }
    }


 };




TEST_F(ResultsImporterTest, testCallMethods){

    int argc = 0;
    char *argv[1];
    QApplication a(argc, argv);

    ResultsExporter resultsExporter;
    ResultsImporter resultsImporter;
    ProjectManager * pm = &ProjectManager::getInstance();
    pm->setProjectsDirectory(tempProjectsDir);
    QString error;
    bool out = pm->createNewProject(testProjectName, &error);


    pm->loadProject(testProjectName);
    QString TrainingResultsDir = pm->getTrainingResultsDir();
    QDir trResDir(TrainingResultsDir);

    QString classResultsDir = pm->getClassificationResultsDir();
    QDir clResDir(classResultsDir);

    copyPath(resultsDir,trResDir.absolutePath());
    copyPath(classiResultsDir,clResDir.absolutePath());

    //EXPECT_TRUE(QFile::copy(fDir,tarDir));
    resultsImporter.updateResultFolderPaths();
    resultsExporter.updateResultFolderPaths();

    SavableResultsWidget* savaBleResultswidget = new TrainingResultsWidget();
    TrainingResultView* trainingResultView = new TrainingResultView(savaBleResultswidget);

    SavableResultsWidget* savaBleResultswidget2 = new TrainingResultsWidget();
    ClassificationResultView* classificationResultView = new ClassificationResultView(savaBleResultswidget2);

     qRegisterMetaType<TrainingResult>();
     qRegisterMetaType<ClassificationResult>();
    //qRegisterMetaType<TrainingResultView>();
    QSignalSpy spy(&resultsImporter, &ResultsImporter::sig_normal_loadTrainingResultData);
    QSignalSpy spy2(&resultsImporter, &ResultsImporter::sig_normal_loadClassificationResultData);
    resultsImporter.slot_comparison_loadTrainingResultData(trainingResultView,"run");
    resultsImporter.slot_comparison_loadClassificationResultData(classificationResultView,"fun");

    spy2.wait(1000);
    spy.wait(1000);
    //QList<QVariant> arguments = spy.takeFirst();
    //TrainingResultView resultView = qvariant_cast<TrainingResultView>(spy.at(0).at(0));
    TrainingResult* result = spy.at(0).at(1).value<TrainingResult*>();
    ClassificationResult* result2 = spy2.at(0).at(1).value<ClassificationResult*>();

    bool success;
    resultsExporter.slot_save_TrainingResult(result, success);
    resultsExporter.slot_save_ClassificationResult(result2, success);


    //TearDown
    QDir projectsDir(tempProjectsDir);
    projectsDir.removeRecursively();
    QApplication::exit();
    EXPECT_TRUE(true);
}
