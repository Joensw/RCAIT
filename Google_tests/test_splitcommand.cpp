#include <gtest/gtest.h>
#include "../model/imageinspectionmodel.h"
#include <QDir>
#include <QSignalSpy>
#include <splitcommand.h>

//check if loading labeled dataset imagefilepaths work
TEST(SplitCommandTest, testSplit){
    QString path = QDir::current().path();
    SplitCommand cmd(path + "/temp_dataset", path + "/dataset/Train", path + "/dataset/Validate", 50, new ProgressablePlugin());
    EXPECT_TRUE(cmd.execute());

    //check if image is in each folder
    QDir dir(path);
    EXPECT_TRUE(dir.cd("dataset/Train/Auto"));
    EXPECT_TRUE(!dir.isEmpty());
    EXPECT_TRUE(dir.cd("../../Validate/Auto"));
    EXPECT_TRUE(!dir.isEmpty());
}

