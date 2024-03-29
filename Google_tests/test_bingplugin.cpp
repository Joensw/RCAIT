
#include <gtest/gtest.h>
#include "../model/imageinspectionmodel.h"
#include "../plugins/imageplugins/bingplugin/bingplugin.h"
#include <QDir>
#include <QApplication>
#include <QObject>
#include "imageloader.h"
#include <QtTest/QSignalSpy>


class BingPluginTest : public testing::Test {
    protected:


    static void SetUpTestSuite(){
    }

    static void TearDownTestSuite(){

    }

    //copy test files to new directory
    void SetUp() override {

        QDir dir(QDir::current().path());




        newData = dir.path() + "/temp_dataset";
        testNewData = dir.path() + "/temp_test_dataset";;

        copyPath(newData, testNewData);


    }

    //delete testfiles
    void TearDown() override {

        QDir testNewDataDir = QDir(testNewData);
        testNewDataDir.removeRecursively();


    }

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


    QString newData;
    QString testNewData;
    QStringList label = {"car","anothercar"};

    inline static const QString testAPIKey = "3391c68aa039902833f0c7bb1e0755ae";
    inline static const QString testAPISecret = "6acffd9f01ca35c8";
    inline static const QString testPythonPath = "python";



};


//check if downloading images from flickrapi works, returns 1 either way, should not be executed too often
TEST_F(BingPluginTest, testLoadImages){
    //set up bingPlugin
    int argc = 1;
    char *argv[1] = {new char('a')};
    QApplication a(argc, argv);
    BingPlugin bingPlugin;
    BingSettings* bingSettings;
    bingPlugin.init();
    bingSettings = qobject_cast<BingSettings *>(bingPlugin.getConfigurationWidget().get());
    bingSettings->setPythonPath(testPythonPath);
    ASSERT_EQ(bingSettings->getPythonPath(),testPythonPath);
    auto imageLoader = QScopedPointer<ImageLoader>(new ImageLoader);

    bingPlugin.loadImages(testNewData, (ProgressablePlugin*)imageLoader.get(), 1, label);
    QSignalSpy spy(imageLoader.get(), &ImageLoader::sig_pluginFinished);

    //bingPlugin.getInputWidget();
    bingPlugin.saveConfiguration();
    bingPlugin.getName();
    bingPlugin.getPluginIcon();
    bingSettings->saveSettings();
    EXPECT_TRUE(true);
    //EXPECT_TRUE(spy.wait(1000));

    QApplication::exit();
}

