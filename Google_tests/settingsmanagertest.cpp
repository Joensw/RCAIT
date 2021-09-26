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

    QDir dir (temporaryDirectory);


    SettingsManager * sm = &SettingsManager::getInstance();

    sm->configureSettingsFile(testDir1, testDir2, testDir3, testDir4);
    QVERIFY(sm->getProjectsDir() == testDir1);
    QVERIFY(sm->getClassificationPluginDir() == testDir2);
    QVERIFY(sm->getImageLoaderPluginDir() == testDir3);
    QVERIFY(sm->getPythonExecutablePath() == testDir4);

    dir.removeRecursively();
}

void SettingsManagerTest::saveDirectories()
{
    QCoreApplication::setOrganizationName("PSE_SS21");
    QCoreApplication::setApplicationName("RCAIT_TESTS");

    QString testDir1 = temporaryDirectory % "/" % "testDir1";
    QString testDir2 = temporaryDirectory % "/" % "testDir2";
    QString testDir3 = temporaryDirectory % "/" % "testDir3";


    SettingsManager * sm = &SettingsManager::getInstance();

    sm->saveProjectsDir(testDir1);
    sm->saveClassificationPluginDir(testDir2);
    sm->saveImageLoaderPluginDir(testDir3);

    QVERIFY(sm->getProjectsDir() == testDir1);
    QVERIFY(sm->getClassificationPluginDir() == testDir2);
    QVERIFY(sm->getImageLoaderPluginDir() == testDir3);
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

    SettingsManager * sm = &SettingsManager::getInstance();
    int counter = 0;
    QString error;
    QVERIFY(sm->applyGlobalSettings(genuineDir1, genuineDir2, genuineDir3, genuineDir4, &error, &counter));
    QVERIFY(counter == 3);

    QVERIFY(sm->verifyDirectories());

    dir.removeRecursively();
}

QTEST_MAIN(SettingsManagerTest);
