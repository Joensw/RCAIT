#include <gtest/gtest.h>
#include <QDir>
#include <datamanager.h>
#include <imageloadcommand.h>
#include <imageloader.h>
#include <qapplication.h>
#include "imageloaderpluginmock.h"

class ImageLoadCommandTest : public testing::Test {
    protected:

    void SetUp() override {
        int argc = 1;
        char *argv[1] = {new char('a')};
        QApplication a(argc, argv);
        path = QDir::current().path();

        mngr.saveImageLoaderPluginDir(path);
        mngr.saveProjectsDir(QDir::current().path());
        mngr.createNewProject("imageload_test");
        mngr.loadProject("imageload_test");
    }

    //delete testfiles
    void TearDown() override {
        mngr.removeProject("imageload_test");
        QApplication::exit();
    }
    DataManager& mngr = DataManager::getInstance();
    QString path;
};

//check if load images command work
TEST_F(ImageLoadCommandTest, testImageLoad){
    QVariantMap map = QVariantMap();
    map.insert("imagePluginName", ImageLoaderPluginMock::PLUGIN_NAME);
    map.insert("count", 100);
    map.insert("labels", QStringList() << "label");
    map.insert("loadMode", 2);
    map.insert("imageFolder", path + "/dataset/Train/Mann");

    //construct and execute command
    ImageLoadCommand cmd(map, new ImageLoader());
    EXPECT_TRUE(cmd.execute());
}

//check if invalid commands are handled properly
TEST_F(ImageLoadCommandTest, testImageLoadFail){
    QVariantMap map = QVariantMap();
    map.insert("imagePluginName", ImageLoaderPluginMock::PLUGIN_NAME);
    map.insert("count", 100);
//    missing lables, should not be valid
//    map.insert("labels", QStringList() << "label");
    map.insert("loadMode", 2);
    map.insert("imageFolder", path + "/dataset/Train/Mann");

    //construct and execute command
    ImageLoadCommand cmd(map, new ImageLoader());
    EXPECT_FALSE(cmd.execute());
}
