#include <gtest/gtest.h>
#include "../model/imageinspectionmodel.h"
#include <QDir>

//check if loading labeled dataset imagefilepaths work
//with a folder "Mann" and 1 image in dataset
TEST(ImageInspectionModelTest, testLoadDataSet){
    ImageInspectionModel iim;
    QDir dir(QDir::current().path());
    dir.cd("dataset");
    iim.loadDataSet(dir.path() + "/training", dir.path() + "/validation");
    EXPECT_TRUE(iim.getTrainDataset().contains("Mann"));
    EXPECT_TRUE(iim.getTrainDataset().value("Mann").isEmpty() == false);
}

//check if new data is loaded and split correctly
//use folder with 10 images of car
//split 40 -> 4 images in validation, 6 in car
TEST(ImageInspectionModelTest, testLoadNewDataSet){
    ImageInspectionModel iim;
    QDir dir(QDir::current().path());
    dir.cd("temp_dataset");
    iim.loadNewData(dir.path(),40);

    QMap<QString, QStringList> valData = iim.getValidationNewData();
    QMap<QString, QStringList> trainData = iim.getTrainNewData();

    EXPECT_EQ(valData.value("Auto").size(), 4);
    EXPECT_EQ(trainData.value("Auto").size(), 6);

}

//check if new data is correctly merged into new dataset
TEST(ImageInspectionModelTest, testMergeDataSets){
    ImageInspectionModel iim;
    QDir dir(QDir::current().path());
    dir.cd("dataset");
    iim.loadDataSet(dir.path() + "/training", dir.path() + "/validation");
    QDir dir2(QDir::current().path());
    dir2.cd("temp_dataset");
    iim.loadNewData(dir2.path(),40);
    iim.mergeDataSets(dir.path() + "/training", dir.path() + "/validation");

    EXPECT_TRUE(iim.getTrainDataset().contains("Auto"));
    EXPECT_EQ(iim.getTrainDataset().value("Auto").size(), 6);
}


TEST(ImageInspectionModelTest, testRemoveImage){
    ImageInspectionModel iim;
    QDir dir(QDir::current().path());
    dir.cd("dataset");
    iim.loadDataSet(dir.path() + "/training", dir.path() + "/validation");
    QDir dir2(QDir::current().path());
    dir2.cd("temp_dataset");
    iim.loadNewData(dir2.path(),40);
    //3 for traindataset
    QMap<QString, QList<int>> removeImages;
    //check if file we want to remove is really in training dataset
    //EXPECT_TRUE(iim.getTrainDataset().value("Auto").contains(dir.path() + "/training/Auto/Auto_1.jpg"));
    //removeImages.insert("Auto",QStringList() << dir.path() + "/training/Auto/Auto_1.jpg");
    QList<int> intList;
    intList.append(1);
    intList.append(2);
    removeImages.insert("Auto", intList);
    iim.removeImage(3,removeImages);

    EXPECT_TRUE(iim.getTrainDataset().contains("Auto"));
    EXPECT_EQ(iim.getTrainDataset().value("Auto").size(), 6-2);
}
