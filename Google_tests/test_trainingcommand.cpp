#include <gtest/gtest.h>
#include <QDir>
#include <datamanager.h>
#include <trainingcommand.h>
#include <qapplication.h>
#include <trainer.h>
#include "classificationpluginmock.h"

//check if valid commands work
TEST(TrainingCommandTest, testClassification){
    //setup
    int argc = 1;
    char *argv[1] = {new char('a')};
    QApplication a(argc, argv);
    QString path = QDir::current().path();
    auto* mngr = &DataManager::getInstance();

    mngr->saveClassificationPluginDir(path);
    mngr->saveProjectsDir(QDir::current().path());
    mngr->createNewProject("trainingcmd_test");
    mngr->loadProject("trainingcmd_test");
    QVariantMap map = QVariantMap();
    map.insert("aiPluginName", ClassificationPluginMock::PLUGIN_NAME);
    map.insert("modelName", "true");
    map.insert("classificationImagePath", "true");
    map.insert("baseModel", "base");
    map.insert("projectName", "name");


    //construct and execute command
    TrainingCommand cmd(map, new Trainer());
    EXPECT_TRUE(cmd.execute());

    //construct command that should return false
    map.remove("modelName");
    map.insert("modelName", "");
    TrainingCommand cmd2(map, new Trainer());
    EXPECT_FALSE(cmd2.execute());

    //remove project dir
    mngr->removeProject("trainingcmd_test");
    QApplication::exit();
}

//check if invalid commands are handled properly
TEST(TrainingCommandTest, testCommandFail){
    //setup
    int argc = 1;
    char *argv[1] = {new char('a')};
    QApplication a(argc, argv);
    QString path = QDir::current().path();
    DataManager* mngr = &DataManager::getInstance();

    mngr->saveImageLoaderPluginDir(path);
    mngr->saveProjectsDir(QDir::current().path());
    mngr->createNewProject("trainingcmd_test");
    mngr->loadProject("trainingcmd_test");
    QVariantMap map = QVariantMap();
    map.insert("aiPluginName", ClassificationPluginMock::PLUGIN_NAME);
//    map.insert("modelName", "true"); should fail without these
//    map.insert("classificationImagePath", "path");
    map.insert("baseModel", "base");
    map.insert("projectName", "name");

    //construct and execute command
    TrainingCommand cmd(map, new Trainer());
    EXPECT_FALSE(cmd.execute());

    //remove project dir
    mngr->removeProject("trainingcmd_test");
    QApplication::exit();
}
