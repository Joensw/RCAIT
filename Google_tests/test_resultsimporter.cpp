#include <QDir>
#include <gtest/gtest.h>
#include <QApplication>
#include "resultsimporter.h"
#include "trainingresultview.h"
#include "trainingresultswidget.h"
#include <QWidget>
#include <QtTest/QSignalSpy>



class ResultsImporterTest : public testing::Test {
    protected:


    static void SetUpTestSuite() {
    }

    static void TearDownTestSuite() {
    }

    void SetUp() override {

        resultsDir = QDir::current().path() + "/results";

    }

    void TearDown() override {

    }


    QString resultsDir;
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

    ResultsImporter resultsImporter;
    ProjectManager * pm = &ProjectManager::getInstance();
    pm->setProjectsDirectory(tempProjectsDir);
    QString error;
    bool out = pm->createNewProject(testProjectName, &error);
    //EXPECT_TRUE(out);
    qDebug() << error;

    pm->loadProject(testProjectName);
    QString TrainingResultsDir = pm->getTrainingResultsDir();
    QDir trResDir(TrainingResultsDir);

    copyPath(resultsDir,trResDir.absolutePath());

    //EXPECT_TRUE(QFile::copy(fDir,tarDir));
    resultsImporter.updateResultFolderPaths();
    SavableResultsWidget* savaBleResultswidget = new TrainingResultsWidget();
    TrainingResultView* trainingResultView = new TrainingResultView(savaBleResultswidget);


    //qRegisterMetaType<TrainingResult>();
    //qRegisterMetaType<TrainingResultView>();
    //QSignalSpy spy(&resultsImporter, &ResultsImporter::sig_normal_loadTrainingResultData);
    resultsImporter.slot_comparison_loadTrainingResultData(trainingResultView,"run");


    //spy.wait(1000);
    //QList<QVariant> arguments = spy.takeFirst();
    //TrainingResultView resultView = qvariant_cast<TrainingResultView>(spy.at(0).at(0));
    //TrainingResult result = qvariant_cast<TrainingResult>(spy.at(0).at(1));

    //TearDown
    QDir projectsDir(tempProjectsDir);
    projectsDir.removeRecursively();
    QApplication::exit();
    EXPECT_TRUE(true);
}
