#include <gtest/gtest.h>
#include "../model/projectmanager.h"

QString tempProjectsDir = "../projects";
QString testProjectName = "testProject";

TEST(ProjectManagerTest, testFalseName){
    ProjectManager * pm = &ProjectManager::getInstance();
    QString error;
    bool out = pm->createNewProject("ThisNameIsNotAllowedBecauseItContains:SpecialCharacters!", &error);
    EXPECT_FALSE(out);
}

TEST(ProjectManagerTest, createValidProject){
    //SetUp
    ProjectManager * pm = &ProjectManager::getInstance();
    pm->setProjectsDirectory(tempProjectsDir);
    QString error;
    bool out = pm->createNewProject(testProjectName, &error);
    EXPECT_TRUE(out);

    QDir testDataDir(tempProjectsDir + "/" + testProjectName + "/" + datasetDirectoryName);
    QDir testTempDir(tempProjectsDir + "/" + testProjectName + "/" + tempDirectoryName);
    QDir testResultsDir(tempProjectsDir + "/" + testProjectName + "/" + resultsDirectoryName);
    EXPECT_TRUE(testDataDir.exists());
    EXPECT_TRUE(testTempDir.exists());
    EXPECT_TRUE(testResultsDir.exists());

    QDir testClassResultsDir(tempProjectsDir + "/" + testProjectName + "/" + resultsDirectoryName + "/" + classificationResultsDirectoryName);
    QDir testTrainResultsDir(tempProjectsDir + "/" + testProjectName + "/" + resultsDirectoryName + "/" + trainingsResultsDirectoryName);
    EXPECT_TRUE(testClassResultsDir.exists());
    EXPECT_TRUE(testTrainResultsDir.exists());

    QFile projFile(tempProjectsDir + "/" + testProjectName + "/" + testProjectName + ".ini");
    EXPECT_TRUE(projFile.exists());

    //QDir testDir("../projects/testProject1");
    QDir testDir(tempProjectsDir + "/" + testProjectName);
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
    bool out = pm->createNewProject(testProjectName, &error);
    EXPECT_TRUE(out);

    pm->removeProject(testProjectName);
    QDir testDir(tempProjectsDir + "/" + testProjectName);
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
    bool out = pm->createNewProject(testProjectName, &error);
    EXPECT_TRUE(out);

    pm->loadProject(testProjectName);

    QDir projectDir(tempProjectsDir + "/" + testProjectName);
    QString projectPath = projectDir.absolutePath();
    EXPECT_TRUE(pm->getProjectPath() == projectPath);
    EXPECT_TRUE(pm->getProjectDataSetDir() == (projectPath + "/" + datasetDirectoryName));
    EXPECT_TRUE(pm->getProjectTempDir() == (projectPath + "/" + tempDirectoryName));

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
    bool out = pm->createNewProject(testProjectName, &error);
    EXPECT_TRUE(out);

    out = pm->createNewProject("anotherTestProject", &error);
    EXPECT_TRUE(out);

    QStringList l = pm->getProjects();

    EXPECT_TRUE(l.contains(testProjectName));
    EXPECT_TRUE(l.contains("anotherTestProject"));

    //TearDown
    projectsDir.removeRecursively();
}





