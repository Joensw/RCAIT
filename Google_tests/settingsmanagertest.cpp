#include "settingsmanagertest.h"

QString temporaryDirectory = "../smTest";


void SettingsManagerTest::qSettingsSimple()
{
    QCoreApplication::setOrganizationName("PSE_SS21");
    QCoreApplication::setApplicationName("RCAIT_TESTS");

    QString testDir1 = temporaryDirectory % "/" % "testDir1";
    QString testDir2 = temporaryDirectory % "/" % "testDir2";
    QString testDir3 = temporaryDirectory % "/" % "testDir3";
    QString testDir4 = temporaryDirectory % "/" % "testDir4";

    QDir dir(temporaryDirectory);


    ConfigurationManager *cm = &ConfigurationManager::getInstance();

    cm->configureSettingsFile(testDir1, testDir2, testDir3, testDir4);
    QVERIFY(cm->getProjectsDir() == testDir1);
    QVERIFY(cm->getClassificationPluginDir() == testDir2);
    QVERIFY(cm->getImageLoaderPluginDir() == testDir3);
    QVERIFY(cm->getPythonExecutablePath() == testDir4);

    dir.removeRecursively();
}

void SettingsManagerTest::saveDirectories()
{
    QCoreApplication::setOrganizationName("PSE_SS21");
    QCoreApplication::setApplicationName("RCAIT_TESTS");

    QString testDir1 = temporaryDirectory % "/" % "testDir1";
    QString testDir2 = temporaryDirectory % "/" % "testDir2";
    QString testDir3 = temporaryDirectory % "/" % "testDir3";


    ConfigurationManager *cm = &ConfigurationManager::getInstance();

    cm->saveProjectsDir(testDir1);
    cm->saveClassificationPluginDir(testDir2);
    cm->saveImageLoaderPluginDir(testDir3);

    QVERIFY(cm->getProjectsDir() == testDir1);
    QVERIFY(cm->getClassificationPluginDir() == testDir2);
    QVERIFY(cm->getImageLoaderPluginDir() == testDir3);
}

void SettingsManagerTest::verifyDirectories()
{
    QString genuineDir1 = temporaryDirectory % "/" % "testDir1";
    QString genuineDir2 = temporaryDirectory % "/" % "testDir2";
    QString genuineDir3 = temporaryDirectory % "/" % "testDir3";
    QString genuineDir4 = temporaryDirectory % "/" % "testDir4";

    QDir dir (temporaryDirectory);

    dir.mkpath(genuineDir1);
    dir.mkpath(genuineDir2);
    dir.mkpath(genuineDir3);
    dir.mkpath(genuineDir4);

    ConfigurationManager *cm = &ConfigurationManager::getInstance();
    SettingsManager *sm = &SettingsManager::getInstance();
    int counter = 0;
    QString error;
    QVERIFY(sm->applyGlobalSettings(genuineDir1, genuineDir2, genuineDir3, genuineDir4, error, counter));
    QVERIFY(counter == 4);

    QVERIFY(cm->verifyDirectories());

    dir.removeRecursively();
}

QTEST_MAIN(SettingsManagerTest);
