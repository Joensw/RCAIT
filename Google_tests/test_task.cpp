#include <gtest/gtest.h>
#include <QtTest/QSignalSpy>
#include "../model/automation/task.h"

class MockCommand : public Command {
 public:
    MockCommand(){}
    bool execute() override{
        for (int i = 1; i <= 100; i++) {
            mProgressable->slot_makeProgress(i);
        }
        return true;
    }

    void setProgressable(ProgressablePlugin* progr){
        mProgressable = progr;
    }

private:
    ProgressablePlugin* mProgressable;
};


//check if running task and percentage signals work
TEST(TaskTest, testruncompleted){
    //set up
    QVariantMap map = QVariantMap();
    map.insert("taskName", "example");
    QList<Command*> cmdList;
    for (int i = 0; i < 3; i++){
        cmdList.append(new MockCommand());
    }
    DataManager* mngr = new DataManager();

    //init task
    Task* task = new Task(map, mngr, cmdList);
    EXPECT_TRUE(task->isValid());

    QSignalSpy spy(task, &Task::sig_progress);

    //register progressable
    for (int i = 0; i < 3; i++){
        ((MockCommand*)cmdList.at(i))->setProgressable(task);
    }

    //test for correct state, then run
    EXPECT_TRUE(task->getState() == TaskState::SCHEDULED);
    task->run();

    EXPECT_EQ(spy.at(151).at(0).toInt(), 50);
    EXPECT_TRUE(task->getName() == "example");
    EXPECT_TRUE(task->getState() == TaskState::COMPLETED);
}

//check if canceling task works
TEST(TaskTest, testruncanceledreset){
    //set up
    QVariantMap map = QVariantMap();
    map.insert("taskName", "example");
    QList<Command*> cmdList;
    for (int i = 0; i < 3; i++){
        cmdList.append(new MockCommand());
    }
    DataManager* mngr = new DataManager();

    //init task
    Task* task = new Task(map, mngr, cmdList);
    QSignalSpy spy(task, &Task::sig_stateChanged);
    EXPECT_TRUE(task->getName() == "example");

    //register progressable
    for (int i = 0; i < 3; i++){
        ((MockCommand*)cmdList.at(i))->setProgressable(task);
    }

    //test for correct state, then run
    EXPECT_EQ(task->getState(), TaskState::SCHEDULED);
    task->abort();
    task->run();
    EXPECT_EQ(task->getState(), TaskState::FAILED);

    //test if task can be reset and run successfuly
    task->resetTask();
    EXPECT_EQ(task->getState(), TaskState::SCHEDULED);
    task->run();
    EXPECT_EQ(task->getState(), TaskState::COMPLETED);

    EXPECT_EQ(spy.at(0).at(1).toInt(), TaskState::PERFORMING);
    EXPECT_EQ(spy.at(1).at(1).toInt(), TaskState::FAILED);
    EXPECT_EQ(spy.at(2).at(1).toInt(), TaskState::PERFORMING);
    EXPECT_EQ(spy.at(3).at(1).toInt(), TaskState::COMPLETED);
}

//check if isValid works
TEST(TaskTest, testisvalid){
    //set up
    QVariantMap map = QVariantMap();
    map.insert("taskName", "example");
    map.insert("projectName", "test");
    DataManager* mngr = new DataManager();

    //init invalid task
    Task* task = new Task(map, mngr);
    EXPECT_FALSE(task->isValid());

    //add elements to map
    map.insert("taskType", QStringList() << "addProject");

    //init valid task
    task = new Task(map, mngr);
    EXPECT_TRUE(task->isValid());

    //add unknown task type as only task type
    map.remove("taskType");
    map.insert("taskType", QStringList() << "unknownCommand");

    //init invalid task
    task = new Task(map, mngr);
    EXPECT_FALSE(task->isValid());
}
