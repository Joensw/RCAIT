#include <gtest/gtest.h>
#include <QStringBuilder>
#include <QDir>
#include <settingsmanager.h>

QString temporaryDirectory = "../smTest";

TEST(SettingsManagerTest, invalidPathsTrivial){
    SettingsManager * sm = &SettingsManager::getInstance();
    QString emptyString = "";
    QString nullString;

    EXPECT_FALSE(sm->verifyPath(nullString));
    EXPECT_FALSE(sm->verifyPath(emptyString));
    EXPECT_FALSE(sm->verifyPaths(nullString, emptyString, nullString));
}

TEST(SettingsManagerTest, duplicatePaths){
    SettingsManager * sm = &SettingsManager::getInstance();
    QString samplePath = "../generic/path/structure";
    QString copySamplePath = samplePath;
    QString differentSamplePath = "../different/generic/strucutre";

    EXPECT_FALSE(sm->verifyPaths(samplePath, copySamplePath, differentSamplePath));
}

TEST(SettingsManagerTest, nonExistentPaths){
    QString genericDir1 = "testDir1";
    QString genericDir2 = "testDir2";
    QString genericDir3 = "testDir3";
    SettingsManager * sm = &SettingsManager::getInstance();

    EXPECT_FALSE(sm->verifyPath(genericDir1));
    EXPECT_FALSE(sm->verifyPaths(genericDir1, genericDir2, genericDir3));
}

TEST(SettingsManagerTest, genuinePaths){
    //create directories prior so they can be found
    QString genuineDir1 = temporaryDirectory % "/" % "testDir1";
    QString genuineDir2 = temporaryDirectory % "/" % "testDir2";
    QString genuineDir3 = temporaryDirectory % "/" % "testDir3";

    QDir dir (temporaryDirectory);
    dir.mkpath(genuineDir1);
    dir.mkpath(genuineDir2);
    dir.mkpath(genuineDir3);

    //check if settingsManager sees them as valid
    SettingsManager * sm = &SettingsManager::getInstance();
    EXPECT_TRUE(sm->verifyPaths(genuineDir1, genuineDir2, genuineDir3));
    dir.removeRecursively();
}

TEST(SettingsManagerTest, applySettingsValid){
    QString genuineDir1 = temporaryDirectory % "/" % "testDir1";
    QString genuineDir2 = temporaryDirectory % "/" % "testDir2";
    QString genuineDir3 = temporaryDirectory % "/" % "testDir3";

    QDir dir (temporaryDirectory);

    dir.mkpath(genuineDir1);
    dir.mkpath(genuineDir2);
    dir.mkpath(genuineDir3);

    SettingsManager * sm = &SettingsManager::getInstance();
    int counter = 0;
    QString error;
    EXPECT_TRUE(sm->applyGlobalSettings(genuineDir1, genuineDir2, genuineDir3, &error, &counter));
    EXPECT_TRUE(counter == 3);

    dir.removeRecursively();
}

