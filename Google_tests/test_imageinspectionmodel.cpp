#include <gtest/gtest.h>
#include "../model/imageinspectionmodel.h"
#include <QDir>

//check if loading labeled dataset imagefilepaths work
TEST(ImageInspectionModelTest, testLoadDataSet){
    ImageInspectionModel iim;
    QDir dir(QDir::current().path());
    dir.cd("dataset");
    iim.loadDataSet(dir.path() + "/Train", dir.path() + "/Validate");
    EXPECT_TRUE(iim.getTrainDataset().contains("Mann"));
    EXPECT_TRUE(iim.getTrainDataset().value("Mann").isEmpty() == false);
}

TEST(ImageInspectionModelTest, DemonstratetTestMacros2){
    ImageInspectionModel img;

    //EXPECT_TRUE(img.VALIDATION_FOLDER.size() != 0);
}


TEST(ImageInspectionModelTest, DemonstratetTestMacros3){


    EXPECT_TRUE(true);
}
