#include <gtest/gtest.h>
#include <imageloader.h>
#include <QApplication>
#include <QDir>
#include <folderplugin/folderplugin.h>

QString testDir = "foldertest";

//check if loading folders as labels works
TEST(FolderPluginTest, testFoldersAsLabels){
    //setup
    int argc = 1;
    char *argv[1] = {new char('a')};
    QApplication a(argc, argv);
    QString path = QDir::current().path();
    QDir dir(path);
    EXPECT_TRUE(dir.mkdir(testDir));
    EXPECT_TRUE(dir.cd(testDir));

    FolderPlugin plugin;
    plugin.init();

    //set image path and mode
    QWidget* config = plugin.getInputWidget();
    config->setProperty("imageFolder", path + "/test_imagefolder");
    config->setProperty("loadMode", 0);
    plugin.saveConfiguration();

    //test load method
    EXPECT_TRUE(plugin.loadImages(dir.absolutePath(), new ImageLoader(), 0, QStringList()));

    //check if files are copied
    EXPECT_TRUE(dir.cd("Auto"));
    EXPECT_EQ(dir.count(), 2 + 2 );
    dir.cdUp();
    EXPECT_TRUE(dir.cd("Flugzeug"));
    EXPECT_EQ(dir.count(), 2 + 2 );
    dir.cdUp();
    EXPECT_TRUE(dir.cd("label_names"));
    EXPECT_EQ(dir.count(), 8 + 2 );
    dir.cdUp();
    EXPECT_TRUE(dir.cd("Truck"));
    EXPECT_EQ(dir.count(), 2 + 2 );
    dir.cdUp();

    //TearDown
    dir = QDir(path + "/" + testDir);
    EXPECT_TRUE(dir.exists());
    dir.removeRecursively();
    a.exit();
}

//check if loading with names as labels works
TEST(FolderPluginTest, testNamesAsLabels){
    //setup
    int argc = 1;
    char *argv[1] = {new char('a')};
    QApplication a(argc, argv);
    QString path = QDir::current().path();
    QDir dir(path);
    EXPECT_TRUE(dir.mkdir(testDir));
    EXPECT_TRUE(dir.cd(testDir));

    FolderPlugin plugin;
    plugin.init();

    //set image path and mode
    QWidget* config = plugin.getInputWidget();
    config->setProperty("imageFolder", path + "/test_imagefolder/label_names");
    config->setProperty("loadMode", 1);
    plugin.saveConfiguration();

    //test load method
    EXPECT_TRUE(plugin.loadImages(dir.absolutePath(), new ImageLoader(), 0, QStringList()));

    //check if files are copied
    EXPECT_EQ(dir.count(), 3 + 2);
    EXPECT_TRUE(dir.cd("label1"));
    EXPECT_EQ(dir.count(), 2 + 2);
    dir.cdUp();
    EXPECT_TRUE(dir.cd("label2"));
    EXPECT_EQ(dir.count(), 2 + 2);
    dir.cdUp();
    EXPECT_TRUE(dir.cd("label3"));
    EXPECT_EQ(dir.count(), 2 + 2);
    dir.cdUp();

    //TearDown
    dir = QDir(path + "/" + testDir);
    EXPECT_TRUE(dir.exists());
    dir.removeRecursively();
    a.exit();
}

//check if loading with single folder as label works
TEST(FolderPluginTest, testFolderAsLabel){
    //setup
    int argc = 1;
    char *argv[1] = {new char('a')};
    QApplication a(argc, argv);
    QString path = QDir::current().path();
    QDir dir(path);
    EXPECT_TRUE(dir.mkdir(testDir));
    EXPECT_TRUE(dir.cd(testDir));

    FolderPlugin plugin;
    plugin.init();

    //set image path and mode
    QWidget* config = plugin.getInputWidget();
    config->setProperty("imageFolder", path + "/test_imagefolder/label_names");
    config->setProperty("loadMode", 2);
    plugin.saveConfiguration();

    //test load method
    EXPECT_TRUE(plugin.loadImages(dir.absolutePath(), new ImageLoader(), 0, QStringList()));

    //check if files are copied
    EXPECT_EQ(dir.count(), 1 + 2);
    EXPECT_TRUE(dir.cd("label_names"));
    EXPECT_EQ(dir.count(), 8 + 2);

    //TearDown
    dir = QDir(path + "/" + testDir);
    EXPECT_TRUE(dir.exists());
    dir.removeRecursively();
    a.exit();
}
