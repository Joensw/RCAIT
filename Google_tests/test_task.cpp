#include <gtest/gtest.h>
#include <QObject>
#include "../model/automation/task.h"

class MockCommand : public Command {
 public:
    MockCommand(){}
    bool execute() override{
        for (int i = 0; i <= 100; i++) {
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


//check if loading labeled dataset imagefilepaths work
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

    //register progressable
    for (int i = 0; i < 3; i++){
        ((MockCommand*)cmdList.at(i))->setProgressable(task);
    }

    task->run();

    EXPECT_TRUE(task->getName() == "example");
    EXPECT_TRUE(task->getState() == TaskState::COMPLETED);


}
