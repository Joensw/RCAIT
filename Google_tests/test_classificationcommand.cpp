#include <gtest/gtest.h>
#include <QDir>
#include <datamanager.h>
#include <classificationcommand.h>
#include <qapplication.h>
#include <classifier.h>
#include "classificationpluginmock.h"

class ClassificationCommandTest : public testing::Test {
    protected:

    void SetUp() override {
        int argc = 1;
        char *argv[1] = {new char('a')};
        QApplication a(argc, argv);
        QString path = QDir::current().path();

        mngr.saveClassificationPluginDir(path);
        mngr.saveProjectsDir(QDir::current().path());
        mngr.createNewProject("classificationcmd_test");
        mngr.loadProject("classificationcmd_test");
    }

    //delete testfiles
    void TearDown() override {
        mngr.removeProject("classificationcmd_test");
        QApplication::exit();
    }
    DataManager& mngr = DataManager::getInstance();
};


//check if valid commands work
TEST_F(ClassificationCommandTest, testClassification){
    QVariantMap map = QVariantMap();
    map.insert("aiPluginName", ClassificationPluginMock::PLUGIN_NAME);
    map.insert("modelName", "true");
    map.insert("classificationImagePath", "true");
    map.insert("projectName", "name");


    //construct and execute command
    auto classifier = QScopedPointer<Classifier>(new Classifier);
    ClassificationCommand cmd(map, &*classifier);
    EXPECT_TRUE(cmd.execute());

    //construct command that should return false
    map.remove("classificationImagePath");
    map.insert("classificationImagePath", "");
    auto classifier2 = QScopedPointer<Classifier>(new Classifier);
    ClassificationCommand cmd2(map, &*classifier);
    EXPECT_FALSE(cmd2.execute());
}

//check if invalid commands are handled properly
TEST_F(ClassificationCommandTest, testCommandFail) {
    QVariantMap map = QVariantMap();
    map.insert("aiPluginName", ClassificationPluginMock::PLUGIN_NAME);
//    map.insert("modelName", "true"); should fail without these
//    map.insert("classificationImagePath", "path");
    map.insert("projectName", "name");

    //construct and execute command
    auto classifier = QScopedPointer<Classifier>(new Classifier);
    ClassificationCommand cmd(map, &*classifier);
    EXPECT_FALSE(cmd.execute());
}
