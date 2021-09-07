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

    EXPECT_TRUE(valData.value("car").size()==4);
    EXPECT_TRUE(trainData.value("car").size()==6);

}


TEST(ImageInspectionModelTest, DemonstratetTestMacros3){
    ImageInspectionModel iim;


    EXPECT_TRUE(true);
}
