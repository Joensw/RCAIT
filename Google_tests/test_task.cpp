#include <gtest/gtest.h>
#include <QtTest/QSignalSpy>
#include <qapplication.h>
#include "../model/automation/task.h"

class MockCommand : public Command {
 public:
    MockCommand()= default;
    bool execute() override{
        for (int i = 1; i <= 100; i++) {
            mProgressable->slot_makeProgress(i);
        }
        return true;
    }

    void setProgressable(ProgressablePlugin* progressablePlugin){
        mProgressable = progressablePlugin;
    }

private:
    ProgressablePlugin* mProgressable{};
};


//check if running task and percentage signals work
TEST(TaskTest, testruncompleted){
    //set up
    int argc = 1;
    char *argv[1] = {new char('a')};
    QApplication a(argc, argv);
    QVariantMap map = QVariantMap();
    map.insert("taskName", "example");
    QList<QSharedPointer<Command>> cmdList;
    for (int i = 0; i < 3; i++){
        cmdList <<QSharedPointer<Command>(new MockCommand);
    }
    [[maybe_unused]] DataManager* mngr = &DataManager::getInstance();

    //init task
    auto task = QScopedPointer<Task>(new Task(map, cmdList));
    EXPECT_TRUE(task->isValid());

    QSignalSpy spy(&*task, &Task::sig_progress);

    //register progressable
    for (int i = 0; i < 3; i++){
        cmdList[i].dynamicCast<MockCommand>()->setProgressable(&*task);
    }

    //test for correct state, then run
    EXPECT_TRUE(task->getState() == TaskState::SCHEDULED);
    task->run();

    EXPECT_EQ(spy.at(151).at(0).toInt(), 50);
    EXPECT_TRUE(task->getName() == "example");
    EXPECT_TRUE(task->getState() == TaskState::COMPLETED);

    //tear down
    QApplication::exit();
}

//check if canceling task works
TEST(TaskTest, testruncanceledreset){
    //set up
    int argc = 1;
    char *argv[1] = {new char('a')};
    QApplication a(argc, argv);
    QVariantMap map = QVariantMap();
    map.insert("taskName", "example");
    QList<QSharedPointer<Command>> cmdList;
    for (int i = 0; i < 3; i++){
        cmdList <<QSharedPointer<Command>(new MockCommand);
    }
    [[maybe_unused]] DataManager* mngr = &DataManager::getInstance();

    //init task
    auto task = QScopedPointer<Task>(new Task(map, cmdList));
    QSignalSpy spy(&*task, &Task::sig_stateChanged);
    EXPECT_TRUE(task->getName() == "example");

    //register progressbar
    for (int i = 0; i < 3; i++){
        cmdList[i].dynamicCast<MockCommand>()->setProgressable(&*task);
    }

    //test for correct state, then run
    EXPECT_EQ(task->getState(), TaskState::SCHEDULED);
    task->abort();
    task->run();
    EXPECT_EQ(task->getState(), TaskState::FAILED);

    //test if task can be reset and run successfully
    task->resetTask();
    EXPECT_EQ(task->getState(), TaskState::SCHEDULED);
    task->run();
    EXPECT_EQ(task->getState(), TaskState::COMPLETED);

    EXPECT_EQ(spy.at(0).at(1).toInt(), TaskState::PERFORMING);
    EXPECT_EQ(spy.at(1).at(1).toInt(), TaskState::FAILED);
    EXPECT_EQ(spy.at(2).at(1).toInt(), TaskState::PERFORMING);
    EXPECT_EQ(spy.at(3).at(1).toInt(), TaskState::COMPLETED);

    //tear down
    QApplication::exit();
}

//check if isValid works
TEST(TaskTest, testisvalid){
    //set up
    int argc = 1;
    char *argv[1] = {new char('a')};
    QApplication a(argc, argv);
    QVariantMap map = QVariantMap();
    map.insert("taskName", "example");
    map.insert("projectName", "test");
    DataManager* mngr = &DataManager::getInstance();
    mngr->saveProjectsDir(QDir::current().path());

    //init invalid task
    auto task = QScopedPointer<Task>(new Task(map));
    EXPECT_FALSE(task->isValid());

    //add elements to map
    map.insert("taskType", QStringList() << "addProject");

    //init valid task
    task.reset(new Task(map));
    EXPECT_TRUE(task->isValid());

    //add unknown task type as only task type
    map.remove("taskType");
    map.insert("taskType", QStringList() << "unknownCommand");

    //init invalid task
    task.reset(new Task(map));
    EXPECT_FALSE(task->isValid());

    //remove created folder
    mngr->removeProject("test");

    //tear down
    QApplication::exit();
}
