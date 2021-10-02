#include <gtest/gtest.h>
#include <QDir>
#include <imageloader.h>
#include <splitcommand.h>




class SplitCommandTest : public testing::Test {
    protected:

    //copy test files to new directory
    void SetUp() override {
        testProjectName = "testProjectSplit";
        QDir dir(QDir::current().path());
        auto* mngr = &DataManager::getInstance();
        mngr->saveProjectsDir(dir.path());
        mngr->createNewProject(testProjectName);
        mngr->loadProject(testProjectName);

        //current dataset, and a temp copy for testing
        dataSetPath = dir.path() + "/test_imagefolder/Auto";
        testDatasetPath = mngr->getProjectImageTempDir();

        copyPath(dataSetPath, testDatasetPath);

    }

    //delete testfiles
    void TearDown() override {
        auto* mngr = &DataManager::getInstance();
        mngr->removeProject(testProjectName);
    }

    void copyPath(QString src, QString dst)
    {
        QDir dir(src);
        if (! dir.exists())
            return;
        QDir destDir(dst);
        destDir.mkdir(dir.dirName());

        for (const QString &f: dir.entryList(QDir::Files)) {
            QFile::copy(src + QDir::separator() + f, dst + QDir::separator() + dir.dirName() + QDir::separator() + f);
        }
    }

    QString dataSetPath;
    QString testDatasetPath;
    QString testProjectName;

};


//check if loading labeled dataset imagefilepaths work
TEST_F(SplitCommandTest, testSplit){
    QString path = QDir::current().path();
    auto* mngr = &DataManager::getInstance();
    QVariantMap map = {{"split", 50}};
    SplitCommand cmd(map, new ImageLoader());
    EXPECT_TRUE(cmd.execute());

    //check if image is in each folder
    QDir dir(mngr->getProjectDataSetTrainSubdir() + "/Auto");
    EXPECT_TRUE(!dir.isEmpty());
    dir = QDir(mngr->getProjectDataSetValSubdir() + "/Auto");
    EXPECT_TRUE(!dir.isEmpty());

}

