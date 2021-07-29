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

    void setProgressable(Progressable* progr){
        mProgressable = progr;
    }

private:
    Progressable* mProgressable;
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

    EXPECT_EQ(spy.at(150).at(0).toInt(), 50);
    EXPECT_TRUE(task->getName() == "example");
    EXPECT_TRUE(task->getState() == TaskState::COMPLETED);
}
