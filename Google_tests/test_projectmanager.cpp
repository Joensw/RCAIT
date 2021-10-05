#include <gtest/gtest.h>
#include <QStringBuilder>
#include <projectmanager.h>

QString tempProjectsDir = "../projectsForTests";
QString testProjectName = "testProject";

TEST(ProjectManagerTest, testFalseName){
    ProjectManager * pm = &ProjectManager::getInstance();
    QString error;
    bool out = pm->createNewProject("ThisNameIsNotAllowedBecauseItContains/SpecialCharacters\\*", error);
    EXPECT_FALSE(out);
}

TEST(ProjectManagerTest, createValidProject){
    //SetUp
    ProjectManager * pm = &ProjectManager::getInstance();
    pm->setProjectsDirectory(tempProjectsDir);
    QString error;
    bool out = pm->createNewProject(testProjectName, error);
    EXPECT_TRUE(pm->loadProject(testProjectName));
    EXPECT_TRUE(out);
    qDebug() << error;

    QDir testDataDir(pm->getProjectDataSetDir());
    QDir testDataTrainDir(pm->getProjectDataSetTrainSubdir());
    QDir testDataValDir(pm->getProjectDataSetValSubdir());
    EXPECT_TRUE(testDataTrainDir.exists());
    EXPECT_TRUE(testDataValDir.exists());
    EXPECT_TRUE(testDataDir.exists());

    QDir testTempImageDir(pm->getProjectImageTempDir());
    QDir testTempAugDir(pm->getProjectAugTempDir());
    QDir testResultsDir(pm->getResultsDir());

    EXPECT_TRUE(testTempImageDir.exists());
    EXPECT_TRUE(testTempAugDir.exists());
    EXPECT_TRUE(testResultsDir.exists());

    QDir testClassResultsDir(pm->getTrainingResultsDir());
    QDir testTrainResultsDir(pm->getClassificationResultsDir());
    EXPECT_TRUE(testClassResultsDir.exists());
    EXPECT_TRUE(testTrainResultsDir.exists());

    QFile projFile(tempProjectsDir % "/" % testProjectName % "/" % testProjectName % ".ini");
    EXPECT_TRUE(projFile.exists());

    QDir testDir(tempProjectsDir % "/" % testProjectName);
    EXPECT_TRUE(testDir.removeRecursively());

    //TearDown
    QDir projectsDir(tempProjectsDir);
    projectsDir.removeRecursively();
}

TEST(ProjectManagerTest, deleteValidProject) {
    //SetUp
    ProjectManager * pm = &ProjectManager::getInstance();
    pm->setProjectsDirectory(tempProjectsDir);
    QString error;
    bool out = pm->createNewProject(testProjectName, error);
    EXPECT_TRUE(out);

    pm->removeProject(testProjectName);
    QDir testDir(tempProjectsDir % "/" % testProjectName);
    EXPECT_FALSE(testDir.exists());

    //TearDown
    QDir projectsDir(tempProjectsDir);
    projectsDir.removeRecursively();
}

TEST(ProjectManagerTest, loadProject){
    QDir projectsDir(tempProjectsDir);
    QString absolutePath = projectsDir.absolutePath();
    //SetUp
    ProjectManager * pm = &ProjectManager::getInstance();
    pm->setProjectsDirectory(absolutePath);
    QString error;
    bool out = pm->createNewProject(testProjectName, error);
    EXPECT_TRUE(out);


    pm->loadProject(testProjectName);
    EXPECT_TRUE(pm->getProjectName() == testProjectName);

    QDir projectDir(tempProjectsDir % "/" % testProjectName);
    QString projectPath = projectDir.absolutePath();

    EXPECT_TRUE(pm->getProjectPath() == projectPath);
    //TearDown
    projectsDir.removeRecursively();
}

TEST(ProjectManagerTest, getProjects){
    QDir projectsDir(tempProjectsDir);
    QString absolutePath = projectsDir.absolutePath();
    //SetUP
    ProjectManager * pm = &ProjectManager::getInstance();
    pm->setProjectsDirectory(absolutePath);
    QString error;
    bool out = pm->createNewProject(testProjectName, error);
    EXPECT_TRUE(out);

    out = pm->createNewProject("anotherTestProject", error);
    EXPECT_TRUE(out);

    QStringList l = pm->getProjects();

    EXPECT_TRUE(l.contains(testProjectName));
    EXPECT_TRUE(l.contains("anotherTestProject"));

    //TearDown
    projectsDir.removeRecursively();
}

TEST (ProjectManagerTest, trainingReults) {
    QDir projectsDir(tempProjectsDir);
    QString absolutePath = projectsDir.absolutePath();
    //SetUP
    ProjectManager * pm = &ProjectManager::getInstance();
    pm->setProjectsDirectory(absolutePath);
    QString error;
    bool out = pm->createNewProject(testProjectName, error);
    EXPECT_TRUE(out);

    pm->loadProject(testProjectName);
    EXPECT_TRUE(pm->getProjectName() == testProjectName);

    QString trainingResultsDir = pm->getTrainingResultsDir();
    qDebug() << trainingResultsDir;
    EXPECT_FALSE(trainingResultsDir.isEmpty());

    QString path = pm->getTrainingResultsDir();

    QDir dir;
    dir.mkpath(path + "/" + "NewResult");

    QStringList results = pm->getNamesOfSavedTrainingResults();
    EXPECT_TRUE(results.length() == 1);
    EXPECT_TRUE(results.contains("NewResult"));

    //TearDown
    projectsDir.removeRecursively();
}

TEST (ProjectManagerTest, workDirSubFolder){
    QDir projectsDir(tempProjectsDir);
    QString absolutePath = projectsDir.absolutePath();
    //SetUP
    ProjectManager * pm = &ProjectManager::getInstance();
    pm->setProjectsDirectory(absolutePath);
    QString error;
    bool out = pm->createNewProject(testProjectName, error);
    EXPECT_TRUE(out);

    pm->loadProject(testProjectName);
    EXPECT_TRUE(pm->getProjectName() == testProjectName);

    QString path = pm->createWorkDirSubfolder("GenericName");

    QDir workDirNewSub(path);
    EXPECT_TRUE(workDirNewSub.exists());

    //TearDown
    projectsDir.removeRecursively();
}






