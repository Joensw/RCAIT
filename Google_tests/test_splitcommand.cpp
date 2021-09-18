#include <gtest/gtest.h>
#include <QDir>
#include <imageloader.h>
#include <splitcommand.h>




class SplitCommandTest : public testing::Test {
    protected:

    //copy test files to new directory
    void SetUp() override {
        QDir dir(QDir::current().path());

        //current dataset, and a temp copy for testing
        dataSetPath = dir.path() + "/dataset";
        testDatasetPath = dir.path() + "/temp_test_imageload_dataset";

        //new data to include in dataset and a temp_test copy for testing
        newData = dir.path() + "/temp_dataset";
        testNewData = dir.path() + "/temp_test_dataset";;


        copyPath(dataSetPath, testDatasetPath);
        copyPath(newData, testNewData);

    }

    //delete testfiles
    void TearDown() override {

        QDir testNewDataDir = QDir(testNewData);
        QDir testDataSetDir = QDir(testDatasetPath);

        testDataSetDir.removeRecursively();
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

    QString dataSetPath;
    QString testDatasetPath;
    QString newData;
    QString testNewData;

};


//check if loading labeled dataset imagefilepaths work
TEST_F(SplitCommandTest, testSplit){
    QString path = QDir::current().path();
    SplitCommand cmd(testNewData, testDatasetPath + "/training", testDatasetPath + "/validation", 50, new ImageLoader());
    EXPECT_TRUE(cmd.execute());

    //check if image is in each folder
    QDir dir(testDatasetPath + "/training/Auto");
    EXPECT_TRUE(!dir.isEmpty());
    dir = QDir(testDatasetPath + "/validation/Auto");
    EXPECT_TRUE(!dir.isEmpty());
}

