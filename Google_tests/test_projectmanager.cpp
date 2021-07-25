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

TEST(ProjectManagerTest, saveClassificationResults) {
    //SetUp
    ProjectManager * pm = &ProjectManager::getInstance();
    pm->setProjectsDirectory(tempProjectsDir);
    QString error;
    bool out = pm->createNewProject(testProjectName, &error);
    EXPECT_TRUE(out);

    //load the project
    pm->loadProject(testProjectName);

    //create fake classificationResult
    QList<QString> list;
    list.append("car");
    list.append("truck");
    list.append("semi");

    QMap<QString, QList<double>> map;

    QList<double> list1;
    list1.append(0.1);
    list1.append(0.2);
    list1.append(0.3);
    QString oneToThree = "123";

    map.insert(oneToThree, list1);

    QList<double> list2;
    list2.append(0.4);
    list2.append(0.5);
    list2.append(0.6);
    QString fourToSix = "456";

    map.insert(fourToSix, list2);

    QImage image(30,30, QImage::Format_RGB32);
    image.fill("red");
    QList<QImage> imageList;
    imageList.append(image);

    ClassificationResult classResultTest(map, list, imageList);

    //serialize it
    pm->saveClassificationResult(classResultTest);



    //deserialize it
    QDir classificationResultsDir(tempProjectsDir + "/" + testProjectName + "/" + resultsDirectoryName + "/" + classificationResultsDirectoryName);
    /*
    qDebug() << "###########################################################################";
    qDebug() << classificationResultsDir.entryList(QDir::Files | QDir::NoDotAndDotDot).at(0);
    qDebug() << "###########################################################################";
    */

    QString serializedResultName = classificationResultsDir.entryList(QDir::Files | QDir::NoDotAndDotDot).at(0);



    QFile file(tempProjectsDir + "/" + testProjectName + "/" + resultsDirectoryName + "/" + classificationResultsDirectoryName + "/" + serializedResultName);
    if (!file.open(QIODevice::ReadOnly)){
       qDebug() << "Could not read file";

    }

    QDataStream in(&file);
    in.setVersion(QDataStream::Qt_6_1);

    QList<QString> constructedList;
    QMap<QString, QList<double>> constructedMap;
    QList<QImage> constructedImageList;

    in >> constructedMap >> constructedList >> constructedImageList;


    file.close();

    //check identical

    constructedList.sort();
    list.sort();

    qDebug() << "###########################################################################";
    qDebug() << constructedImageList.at(0);
    qDebug() << imageList.at(0);
    qDebug() << "###########################################################################";

    EXPECT_TRUE(list == constructedList);

    EXPECT_TRUE(constructedImageList.at(0) == imageList.at(0));





    EXPECT_TRUE(constructedMap.size() == map.size()
                && std::equal(constructedMap.begin(), constructedMap.end(),
                              map.begin()));

    //TearDown
    QDir projectsDir(tempProjectsDir);
    projectsDir.removeRecursively();

}




