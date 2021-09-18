#include <gtest/gtest.h>
#include <QDir>
#include <QSignalSpy>
#include <qapplication.h>
#include <classifier.h>
#include <classificationpluginmock.h>
#include <datamanager.h>

//check if classifier works with correct classification
TEST(ClassifierTest, testClassification){
    //setup
    int argc;
    char *argv[1];
    QApplication a(argc, argv);
    QString path = QDir::current().path();
    auto* mngr = &DataManager::getInstance();
    mngr->saveClassificationPluginDir(path);


    //construct classifier
    Classifier* cls = new Classifier;
    QSignalSpy spy(cls, &Classifier::sig_classificationResultUpdated);

    //start classification
    cls->classify(ClassificationPluginMock::PLUGIN_NAME, "true", "true", "true", "true");
    using namespace std::chrono_literals;
    std::this_thread::sleep_for(2ms);

    //check if classificationresults are sent
    cls->slot_handleClassificationResult();
    EXPECT_EQ(spy.size(), 1);

    //tear down
    QApplication::exit();
}

//check if classifier works with incorrect classification
TEST(ClassifierTest, testClassificationFailed){
    //setup
    int argc;
    char *argv[1];
    QApplication a(argc, argv);
    QString path = QDir::current().path();
    auto* mngr = &DataManager::getInstance();
    mngr->saveClassificationPluginDir(path);


    //construct classifier
    Classifier* cls = new Classifier;
    QSignalSpy spy(cls, &Classifier::sig_classificationResultUpdated);
    QSignalSpy spyProgress(cls, &Classifier::sig_progress);

    //start classification
    cls->classify(ClassificationPluginMock::PLUGIN_NAME, "", "", "", "");
    using namespace std::chrono_literals;
    std::this_thread::sleep_for(2ms);

    //check if no classificationresults are sent
    cls->slot_handleClassificationResult();
    EXPECT_EQ(spy.size(), 0);
    //and progress is reported nonetheless
    EXPECT_EQ(spyProgress.size(), 2);
    EXPECT_EQ(spyProgress.at(1).at(0).toInt(), 100);

    //tear down
    QApplication::exit();
}
