#include <gtest/gtest.h>
#include <QDir>
#include <datamanager.h>
#include <classificationcommand.h>
#include <qapplication.h>
#include <classifier.h>
#include "classificationpluginmock.h"

//check if valid commands work
TEST(ClassificationCommandTest, testClassification){
    //setup
    int argc;
    char *argv[1];
    QApplication a(argc, argv);
    QString path = QDir::current().path();
    auto* mngr = &DataManager::getInstance();

    mngr->saveClassificationPluginDir(path);
    mngr->saveProjectsDir(QDir::current().path());
    mngr->createNewProject("classificationcmd_test");
    mngr->loadProject("classificationcmd_test");
    QVariantMap map = QVariantMap();
    map.insert("aiPluginName", ClassificationPluginMock::PLUGIN_NAME);
    map.insert("modelName", "true");
    map.insert("classificationImagePath", "true");
    map.insert("projectName", "name");


    //construct and execute command
    ClassificationCommand cmd(map, mngr->getProjectDataSetTrainSubdir(), new Classifier());
    EXPECT_TRUE(cmd.execute());

    //construct command that should return false
    map.remove("classificationImagePath");
    map.insert("classificationImagePath", "");
    ClassificationCommand cmd2(map, mngr->getProjectDataSetTrainSubdir(), new Classifier());
    EXPECT_FALSE(cmd2.execute());

    //remove project dir
    mngr->removeProject("classificationcmd_test");
    QApplication::exit();
}

//check if invalid commands are handled properly
TEST(ClassificationCommandTest, testCommandFail){
    //setup
    int argc;
    char *argv[1];
    QApplication a(argc, argv);
    QString path = QDir::current().path();
    DataManager* mngr = &DataManager::getInstance();

    mngr->saveImageLoaderPluginDir(path);
    mngr->saveProjectsDir(QDir::current().path());
    mngr->createNewProject("classificationcmd_test");
    mngr->loadProject("classificationcmd_test");
    QVariantMap map = QVariantMap();
    map.insert("aiPluginName", ClassificationPluginMock::PLUGIN_NAME);
//    map.insert("modelName", "true"); should fail without these
//    map.insert("classificationImagePath", "path");
    map.insert("projectName", "name");

    //construct and execute command
    ClassificationCommand cmd(map, mngr->getProjectDataSetTrainSubdir(), new Classifier());
    EXPECT_FALSE(cmd.execute());

    //remove project dir
    mngr->removeProject("classificationcmd_tests");
    QApplication::exit();
}
