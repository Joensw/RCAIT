#include <gtest/gtest.h>
#include <QStringBuilder>
#include <QDir>
#include <settingsmanager.h>


QString temporaryDirectory = "../smTest";
QStringList sampleCPluginNames = {"CPL1", "CPL2", "CPL3"};


TEST(SettingsManagerTest, invalidPathsTrivial){
    QString emptyString = "";
    QString nullString;

    EXPECT_FALSE(ConfigurationManager::verifyPaths({nullString}));
    EXPECT_FALSE(ConfigurationManager::verifyPaths({emptyString}));
    EXPECT_FALSE(ConfigurationManager::verifyPaths({nullString, emptyString, nullString}));
}

TEST(SettingsManagerTest, duplicatePaths) {
    QString samplePath = "../generic/path/structure";
    QString copySamplePath = samplePath;
    QString differentSamplePath = "../different/generic/strucutre";

    EXPECT_FALSE(ConfigurationManager::verifyPaths({samplePath, copySamplePath, differentSamplePath}));
}

TEST(SettingsManagerTest, nonExistentPaths) {
    QString genericDir1 = "testDir1";
    QString genericDir2 = "testDir2";
    QString genericDir3 = "testDir3";

    EXPECT_FALSE(ConfigurationManager::verifyPaths({genericDir1}));
    EXPECT_FALSE(ConfigurationManager::verifyPaths({genericDir1, genericDir2, genericDir3}));
}

TEST(SettingsManagerTest, genuinePaths){
    //create directories prior so they can be found
    QString genuineDir1 = temporaryDirectory % "/" % "testDir1";
    QString genuineDir2 = temporaryDirectory % "/" % "testDir2";
    QString genuineDir3 = temporaryDirectory % "/" % "testDir3";

    QDir dir(temporaryDirectory);
    dir.mkpath(genuineDir1);
    dir.mkpath(genuineDir2);
    dir.mkpath(genuineDir3);

    //check if settingsManager sees them as valid
    EXPECT_TRUE(ConfigurationManager::verifyPaths({genuineDir1, genuineDir2, genuineDir3}));
    dir.removeRecursively();
}

TEST(SettingsManagerTest, applySettingsValid){
    QString genuineDir1 = temporaryDirectory % "/" % "testDir1";
    QString genuineDir2 = temporaryDirectory % "/" % "testDir2";
    QString genuineDir3 = temporaryDirectory % "/" % "testDir3";
    QString genuineDir4 = temporaryDirectory % "/" % "testDir4";

    QDir dir (temporaryDirectory);

    dir.mkpath(genuineDir1);
    dir.mkpath(genuineDir2);
    dir.mkpath(genuineDir3);
    dir.mkpath(genuineDir4);

    SettingsManager * sm = &SettingsManager::getInstance();
    int counter = 0;
    QString error;
    EXPECT_TRUE(sm->applyGlobalSettings(genuineDir1, genuineDir2, genuineDir3, genuineDir4, error, counter));
    EXPECT_TRUE(counter == 4);

    dir.removeRecursively();
}

TEST(SettingsManagerTest, initialisationChecks){
    SettingsManager *sm = &SettingsManager::getInstance();
    ConfigurationManager *cm = &ConfigurationManager::getInstance();

    QStringList allNames = sm->getPluginNames();
    QStringList cNames = sm->getClassificationPluginNames();
    QStringList cBases = sm->getClassificationPluginBase("nonExistantPlugin");
    QStringList iNames = sm->getImageLoaderPluginNames();
    QList<QSharedPointer<QWidget>> widgets = sm->getPluginSettings();

    EXPECT_TRUE(allNames.isEmpty());
    EXPECT_TRUE(cNames.isEmpty());
    EXPECT_TRUE(cBases.isEmpty());
    EXPECT_TRUE(iNames.isEmpty());
    EXPECT_TRUE(widgets.isEmpty());

    EXPECT_FALSE(cm->verifyDirectories());

}

