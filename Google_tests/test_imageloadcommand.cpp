#include <gtest/gtest.h>
#include <QDir>
#include <datamanager.h>
#include <imageloadcommand.h>
#include <qapplication.h>

//check if load images command work
TEST(ImageLoadCommandTest, testImageLoad){
    //setup
    int argc;
    char *argv[1];
    QApplication a(argc, argv);
    QString path = QDir::current().path();
    DataManager* mngr = new DataManager();
    mngr->saveImageLoaderPluginDir(path + "/../plugins/imageplugins/plugins");
    mngr->saveProjectsDir(QDir::current().path());
    mngr->createNewProject("imageload_test");
    mngr->loadProject("imageload_test");
    QVariantMap map = QVariantMap();
    map.insert("imagePluginName", "FolderPlugin");
    map.insert("count", 100);
    map.insert("labels", QStringList() << "label");
    map.insert("loadMode", 2);
    map.insert("imageFolder", path + "/dataset/Train/Mann");

    //construct and execute command
    ImageLoadCommand cmd(map, mngr->getProjectImageTempDir(), new ProgressablePlugin());
    EXPECT_TRUE(cmd.execute());

    //check if image is copied to temp folder
    QDir dir(path);
    EXPECT_TRUE(dir.cd("imageload_test/temp_Images/Mann"));
    QStringList entries = dir.entryList(QDir::AllDirs | QDir::NoDotAndDotDot);
    EXPECT_EQ(entries.size(), 0);
    entries = dir.entryList(QDir::Files);
    EXPECT_EQ(entries.size(), 1);
    EXPECT_EQ(entries.at(0), "thumb.png");

    //remove project dir
    mngr->removeProject("imageload_test");
    a.exit();
}

//check if invalid commands are handled properly
TEST(ImageLoadCommandTest, testImageLoadFail){
    //setup
    int argc;
    char *argv[1];
    QApplication a(argc, argv);
    QString path = QDir::current().path();
    DataManager* mngr = new DataManager();
    mngr->saveImageLoaderPluginDir(path + "/../plugins/imageplugins/plugins");
    mngr->saveProjectsDir(QDir::current().path());
    mngr->createNewProject("imageload_test");
    mngr->loadProject("imageload_test");
    QVariantMap map = QVariantMap();
    map.insert("imagePluginName", "FolderPlugin");
    map.insert("count", 100);
//    missing lables, should not be valid
//    map.insert("labels", QStringList() << "label");
    map.insert("loadMode", 2);
    map.insert("imageFolder", path + "/dataset/Train/Mann");

    //construct and execute command
    ImageLoadCommand cmd(map, mngr->getProjectImageTempDir(), new ProgressablePlugin());
    EXPECT_FALSE(cmd.execute());

    //check if temp image dir is empty
    QDir dir(path);
    EXPECT_FALSE(dir.cd("imageload_test/temp_Images/Mann"));

    //remove project dir
    mngr->removeProject("imageload_test");
    a.exit();
}
