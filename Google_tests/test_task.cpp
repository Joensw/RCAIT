#include <gtest/gtest.h>
#include <QtTest/QSignalSpy>
#include "../model/automation/task.h"

class MockCommand : public Command {
 public:
    MockCommand(){}
    bool execute() override{
        for (int i = 1; i <= 100; i++) {
            if (mCancel) return false;
            mProgressable->slot_makeProgress(i);
        }
        return true;
    }

    void setProgressable(ProgressablePlugin* progr){
        mProgressable = progr;
        connect(mProgressable, &ProgressablePlugin::sig_pluginAborted, this, &MockCommand::abort);
    }

private slots:
    void abort()
    {
        mCancel = true;
    }

private:
    ProgressablePlugin* mProgressable;
    bool mCancel = false;
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
TEST(TaskTest, testruncanceled){
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

    //register progressable
    for (int i = 0; i < 3; i++){
        ((MockCommand*)cmdList.at(i))->setProgressable(task);
    }

    //test for correct state, then run
    EXPECT_TRUE(task->getState() == TaskState::SCHEDULED);
    task->abort();
    task->run();

    EXPECT_EQ(spy.at(0).at(1).toInt(), TaskState::PERFORMING);
    EXPECT_EQ(spy.at(1).at(1).toInt(), TaskState::FAILED);
    EXPECT_TRUE(task->getName() == "example");
    EXPECT_EQ(task->getState(), TaskState::FAILED);
}
