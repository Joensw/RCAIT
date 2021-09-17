#include <gtest/gtest.h>
#include "../model/imageinspectionmodel.h"
#include <QDir>


class ImageInspectionModelTest : public testing::Test {
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
//with a folder "Mann" and 1 image in dataset
TEST_F(ImageInspectionModelTest, testLoadDataSet){
    ImageInspectionModel iim;

    iim.loadDataSet(testDatasetPath + "/training", testDatasetPath + "/validation");
    EXPECT_TRUE(iim.getTrainDataset().contains("Mann"));
    EXPECT_TRUE(iim.getTrainDataset().value("Mann").isEmpty() == false);
}

//check if new data is loaded and split correctly
//use folder with 10 images of car
//split 40 -> 4 images in validation, 6 in car
TEST_F(ImageInspectionModelTest, testLoadNewDataSet){
    ImageInspectionModel iim;

    iim.loadNewData(testNewData,40);

    QMap<QString, QStringList> valData = iim.getValidationNewData();
    QMap<QString, QStringList> trainData = iim.getTrainNewData();

    EXPECT_EQ(valData.value("Auto").size(), 4);
    EXPECT_EQ(trainData.value("Auto").size(), 6);

}

//check if new data is correctly merged into new dataset
TEST_F(ImageInspectionModelTest, testMergeDataSets){
    ImageInspectionModel iim;

    iim.loadDataSet(testDatasetPath + "/training", testDatasetPath + "/validation");

    iim.loadNewData(testNewData,40);
    iim.mergeDataSets(testDatasetPath + "/training", testDatasetPath + "/validation");

    QStringList trainingLabeledFolders = QDir(testDatasetPath + "/training").entryList();
    QStringList trainingImages = QDir(testDatasetPath + "/training/Auto").entryList();

    EXPECT_TRUE(trainingLabeledFolders.contains("Auto"));
    //6 images + dot + dotdot
    EXPECT_EQ(trainingImages.size(), 6+2);
}


TEST_F(ImageInspectionModelTest, testRemoveImage){
    ImageInspectionModel iim;
    iim.loadDataSet(testDatasetPath + "/training", testDatasetPath + "/validation");
    iim.loadNewData(testNewData,40);
    iim.mergeDataSets(testDatasetPath + "/training", testDatasetPath + "/validation");

    //need to load data, because maps dont update without loading again
    iim.loadDataSet(testDatasetPath + "/training", testDatasetPath + "/validation");

    QMap<QString, QList<int>> removeImages;
    QList<int> intList;
    intList.append(0);
    intList.append(1);
    removeImages.insert("Auto", intList);

    iim.removeImage(3,removeImages);

    //check if two files have been deleted

    QStringList trainingLabeledFolders = QDir(testDatasetPath + "/training").entryList();
    QStringList trainingImages = QDir(testDatasetPath + "/training/Auto").entryList();

    EXPECT_TRUE(trainingLabeledFolders.contains("Auto"));
    //6 images + dot + dotdot - 2 images
    EXPECT_EQ(trainingImages.size(), 6+2-2);

}
