
#include <gtest/gtest.h>
#include "../model/imageinspectionmodel.h"
#include "../plugins/imageplugins/flickrplugin/flickrplugin.h"
#include <QDir>
#include <QApplication>
#include <QObject>
#include "imageloader.h"
#include <QtTest/QSignalSpy>
#include "imagepluginerrorutil.h"


class FlickrPluginTest : public testing::TestWithParam<QStringList> {
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
TEST_F(FlickrPluginTest, testLoadImages){
    //set up flickrplugin
    int argc = 1;
    char *argv[1] = {new char('a')};
    QApplication a(argc, argv);
    FlickrPlugin flickrPlugin;
    FlickrSettings *flickrSettings;
    flickrPlugin.init();
    flickrSettings = qobject_cast<FlickrSettings *>(flickrPlugin.getConfigurationWidget().get());
    flickrSettings->setAPIKey(testAPIKey);
    flickrSettings->setAPISecret(testAPISecret);
    flickrSettings->setPythonPath(testPythonPath);

    ASSERT_EQ(flickrSettings->getAPIKey(), testAPIKey);
    ASSERT_EQ(flickrSettings->getAPISecret(), testAPISecret);
    ASSERT_EQ(flickrSettings->getPythonPath(), testPythonPath);
    auto imageLoader = QScopedPointer<ImageLoader>(new ImageLoader);

    QSignalSpy spy(&*imageLoader, &ImageLoader::sig_pluginFinished);
    flickrPlugin.loadImages(testNewData, (ProgressablePlugin *) imageLoader, 1, label);

    flickrPlugin.saveConfiguration();
    flickrPlugin.getName();
    flickrSettings->saveSettings();

    EXPECT_EQ(QDir(testNewData + "/car").entryInfoList(QDir::NoDotAndDotDot | QDir::AllEntries).count(), 1);
    EXPECT_EQ(QDir(testNewData + "/anothercar").entryInfoList(QDir::NoDotAndDotDot | QDir::AllEntries).count(), 1);
    QApplication::exit();
}

TEST_P(FlickrPluginTest, testMissingSetting){
    //set up flickrplugin
    int argc = 1;
    char *argv[1] = {new char('a')};
    QApplication a(argc, argv);
    QStringList testParam = GetParam();
    FlickrPlugin flickrPlugin;
    FlickrSettings* flickrSettings;
    flickrPlugin.init();
    flickrSettings = qobject_cast<FlickrSettings *>(flickrPlugin.getConfigurationWidget().get());
    flickrSettings->setAPIKey(testParam.at(0));
    flickrSettings->setAPISecret(testParam.at(1));
    flickrSettings->setPythonPath(testParam.at(2));

    ASSERT_EQ(flickrSettings->getAPIKey(), testParam.at(0));
    ASSERT_EQ(flickrSettings->getAPISecret(), testParam.at(1));
    ASSERT_EQ(flickrSettings->getPythonPath(), testParam.at(2));

    auto imageLoader = QScopedPointer<ImageLoader>(new ImageLoader);
    QSignalSpy spy(&*imageLoader, &ImageLoader::sig_statusUpdate);
    flickrPlugin.loadImages(testNewData, (ProgressablePlugin *) imageLoader, 1, label);

    //spy.wait(2000);
    EXPECT_EQ(spy.count(), 1); // make sure the signal was emitted exactly one time
    QList<QVariant> arguments = spy.takeFirst();
    auto msg = arguments.at(0).value<QString>();
    EXPECT_EQ(msg, testParam.at(3));

}

INSTANTIATE_TEST_SUITE_P(
        SettingsTests,
        FlickrPluginTest,
        //check all combinatiosn for APIKEY, APISECRET, PYTHONPATH, ERRORMESSAGE
        ::testing::Values(QStringList() << "" << "" << "" << "Error: Python Path, API Secret, API Key not set.",
                          QStringList() << "" << "" << "a" << "Error: API Secret, API Key not set.",
                          QStringList() << "" << "a" << "" << "Error: Python Path, API Key not set.",
                          QStringList() << "" << "a" << "a" << "Error: API Key not set.",
                          QStringList() << "a" << "" << "" << "Error: Python Path, API Secret not set.",
                          QStringList() << "a" << "" << "a" << "Error: API Secret not set.",
                          QStringList() << "a" << "a" << "" << "Error: Python Path not set."
                          //no signal is emitted if all settings are set
                          //QStringList() << "a" << "a" << "a" << "All settings are set."
                ));


class FlickrPluginTestInputs : public testing::TestWithParam<std::tuple<QString, int, QStringList, QString>> {
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

INSTANTIATE_TEST_SUITE_P(
        InputTest,
        FlickrPluginTestInputs,
        //check all combinatiosn for APIKEY, APISECRET, PYTHONPATH, ERRORMESSAGE
        ::testing::Values(std::make_tuple("", 10, QStringList() << "car" << "house", imagepluginerrorutil::getErrorString(QStringList() << imagepluginerrorutil::PATH_EMPTY_ERROR)),
                          std::make_tuple("", 10, QStringList(), imagepluginerrorutil::getErrorString(QStringList() << imagepluginerrorutil::PATH_EMPTY_ERROR << imagepluginerrorutil::LABEL_EMPTY_ERROR)),
                          std::make_tuple("", 0, QStringList() << "car" << "house", imagepluginerrorutil::getErrorString(QStringList() << imagepluginerrorutil::PATH_EMPTY_ERROR << imagepluginerrorutil::COUNT_INVALID_ERROR)),
                          std::make_tuple("", 0, QStringList(), imagepluginerrorutil::getErrorString(QStringList() << imagepluginerrorutil::PATH_EMPTY_ERROR << imagepluginerrorutil::COUNT_INVALID_ERROR << imagepluginerrorutil::LABEL_EMPTY_ERROR)),
                          std::make_tuple("path", 10, QStringList(), imagepluginerrorutil::getErrorString(QStringList() << imagepluginerrorutil::LABEL_EMPTY_ERROR)),
                          std::make_tuple("path", 0, QStringList() << "car" << "house", imagepluginerrorutil::getErrorString(QStringList() << imagepluginerrorutil::COUNT_INVALID_ERROR)),
                          std::make_tuple("path", 0, QStringList(), imagepluginerrorutil::getErrorString(QStringList() << imagepluginerrorutil::COUNT_INVALID_ERROR << imagepluginerrorutil::LABEL_EMPTY_ERROR))
                          //case with supplied arguments does not generate error
                          //std::make_tuple("path", 10, QStringList() << "car" << "house", "")
                ));

TEST_P(FlickrPluginTestInputs, testMissingSetting){
    //set up flickrplugin
    int argc = 1;
    char *argv[1] = {new char('a')};
    QApplication a(argc, argv);
    std::tuple testParam = GetParam();
    FlickrPlugin flickrPlugin;
    FlickrSettings *flickrSettings;
    flickrPlugin.init();
    flickrSettings = qobject_cast<FlickrSettings *>(flickrPlugin.getConfigurationWidget().get());
    flickrSettings->setAPIKey(testAPIKey);
    flickrSettings->setAPISecret(testAPISecret);
    flickrSettings->setPythonPath(testPythonPath);

    auto imageLoader = QScopedPointer<ImageLoader>(new ImageLoader);
    QSignalSpy spy(&*imageLoader, &ImageLoader::sig_statusUpdate);
    flickrPlugin.loadImages(std::get<0>(testParam), (ProgressablePlugin *) imageLoader, std::get<1>(testParam),
                            std::get<2>(testParam));

    //spy.wait(2000);
    EXPECT_EQ(spy.count(), 1); // make sure the signal was emitted exactly one time
    QList<QVariant> arguments = spy.takeFirst();
    auto msg = arguments.at(0).value<QString>();
    EXPECT_EQ(msg, std::get<3>(testParam));

}
