#include <gtest/gtest.h>
#include <QDir>
#include <datamanager.h>
#include <trainingcommand.h>
#include <qapplication.h>
#include <trainer.h>
#include "classificationpluginmock.h"

class TrainingCommandTest : public testing::Test {
    protected:

    void SetUp() override {
        int argc = 1;
        char *argv[1] = {new char('a')};
        QApplication a(argc, argv);
        QString path = QDir::current().path();

        mngr.saveClassificationPluginDir(path);
        mngr.saveProjectsDir(QDir::current().path());
        mngr.createNewProject("trainingcmd_test");
        mngr.loadProject("trainingcmd_test");
    }

    //delete testfiles
    void TearDown() override {
        mngr.removeProject("trainingcmd_test");
        QApplication::exit();
    }
    DataManager& mngr = DataManager::getInstance();
};

//check if valid commands work
TEST_F(TrainingCommandTest, testClassification){
    QVariantMap map = QVariantMap();
    map.insert("aiPluginName", ClassificationPluginMock::PLUGIN_NAME);
    map.insert("modelName", "true");
    map.insert("classificationImagePath", "true");
    map.insert("baseModel", "base");
    map.insert("projectName", "name");

    //construct and execute command
    auto trnr = QScopedPointer<Trainer>(new Trainer);
    TrainingCommand cmd(map, &*trnr);
    EXPECT_TRUE(cmd.execute());

    //construct command that should return false
    map.remove("modelName");
    map.insert("modelName", "");
    auto trnr2 = QScopedPointer<Trainer>(new Trainer);
    TrainingCommand cmd2(map, &*trnr2);
    EXPECT_FALSE(cmd2.execute());
}

//check if invalid commands are handled properly
TEST_F(TrainingCommandTest, testCommandFail) {
    QVariantMap map = QVariantMap();
    map.insert("aiPluginName", ClassificationPluginMock::PLUGIN_NAME);
//    map.insert("modelName", "true"); should fail without these
//    map.insert("classificationImagePath", "path");
    map.insert("baseModel", "base");
    map.insert("projectName", "name");

    //construct and execute command
    auto trnr = QScopedPointer<Trainer>(new Trainer);
    TrainingCommand cmd(map, &*trnr);
    EXPECT_FALSE(cmd.execute());
}
