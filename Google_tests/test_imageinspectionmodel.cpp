#include <gtest/gtest.h>
#include "../model/imageinspectionmodel.h"
#include <QDir>

//check if loading labeled dataset imagefilepaths work
TEST(ImageInspectionModelTest, testLoadDataSet){
    ImageInspectionModel iim;
    QDir dir(QDir::current().path());
    dir.cd("dataset");
    iim.loadDataSet(dir.path());
    QMap<QString, QStringList> trainDataSet = iim.getTrainDataset();
    EXPECT_TRUE(trainDataSet.keys().contains("Mann"));
    EXPECT_TRUE(trainDataSet.value("Mann").isEmpty() == false);

}

TEST(ImageInspectionModelTest, DemonstratetTestMacros2){
    ImageInspectionModel img;

    EXPECT_TRUE(img.VALIDATION_FOLDER.size() != 0);
}


TEST(ImageInspectionModelTest, DemonstratetTestMacros3){


    EXPECT_TRUE(true);
}
