#include <gtest/gtest.h>
#include <QSignalSpy>
#include "../model/automation/automator.h"

//check if loading labeled dataset imagefilepaths work
TEST(AutomatorTest, testAddTask){
    //set up
    DataManager* manager = new DataManager;
    Automator* automator = new Automator(manager);
    QDir dir(QDir::current().path());
    dir.cd("tasks");

    //try adding invalid task
    automator->addTasks(dir.path() + "/task_invalid.json");
    EXPECT_EQ(automator->getUnqueuedSize(), 0);

    //try adding valid task
    automator->addTasks(dir.path() + "/task1.json");
    EXPECT_EQ(automator->getUnqueuedSize(), 1);

    //try adding duplicate (same "taskName")
    automator->addTasks(dir.path() + "/task1_duplicate.json");
    EXPECT_EQ(automator->getUnqueuedSize(), 1);

    //try adding second valid task
    automator->addTasks(dir.path() + "/task2.json");
    EXPECT_EQ(automator->getUnqueuedSize(), 2);
}

//tests if queueing/unqueuing work as expected
TEST(AutomatorTest, testUnQueueTask){
    //set up
    DataManager* manager = new DataManager;
    Automator* automator = new Automator(manager);
    QSignalSpy spy(automator, &Automator::sig_taskUpdate);
    QDir dir(QDir::current().path());
    dir.cd("tasks");
    automator->addTasks(dir.path() + "/task1.json");
    automator->addTasks(dir.path() + "/task2.json");
    automator->addTasks(dir.path() + "/task3.json");

    //invalid index should crash program
    EXPECT_DEATH(automator->queue(3), "");

    //valid queueing
    automator->queue(2);
    automator->queue(1);
    EXPECT_EQ(automator->getUnqueuedSize(), 1);
    EXPECT_EQ(automator->getQueuedSize(), 2);

    //valid unqueueing
    automator->unqueue(0);
    EXPECT_EQ(automator->getUnqueuedSize(), 2);
    EXPECT_EQ(automator->getQueuedSize(), 1);

    //Check if correct status messages were sent
    EXPECT_EQ(spy.at(0).at(0).toString(), "task1");
    EXPECT_EQ(spy.at(0).at(1).toString(), "Not_Scheduled");
    EXPECT_EQ(spy.at(1).at(0).toString(), "task2");
    EXPECT_EQ(spy.at(1).at(1).toString(), "Not_Scheduled");
    EXPECT_EQ(spy.at(2).at(0).toString(), "task3");
    EXPECT_EQ(spy.at(2).at(1).toString(), "Not_Scheduled");
    EXPECT_EQ(spy.at(3).at(0).toString(), "task3");
    EXPECT_EQ(spy.at(3).at(1).toString(), "Scheduled");
    EXPECT_EQ(spy.at(4).at(0).toString(), "task2");
    EXPECT_EQ(spy.at(4).at(1).toString(), "Scheduled");
    EXPECT_EQ(spy.at(5).at(0).toString(), "task3");
    EXPECT_EQ(spy.at(5).at(1).toString(), "Not_Scheduled");
}

TEST(AutomatorTest, testRemove){
    //set up
    DataManager* manager = new DataManager;
    Automator* automator = new Automator(manager);
    QDir dir(QDir::current().path());
    dir.cd("tasks");

    //invalid index should crash program
    EXPECT_DEATH(automator->remove(0), "");

    automator->addTasks(dir.path() + "/task1.json");
    automator->addTasks(dir.path() + "/task2.json");
    automator->addTasks(dir.path() + "/task3.json");
    EXPECT_EQ(automator->getUnqueuedSize(), 3);

    //test valid remove operations
    automator->remove(2);
    EXPECT_EQ(automator->getUnqueuedSize(), 2);
    automator->remove(0);
    EXPECT_EQ(automator->getUnqueuedSize(), 1);
    automator->remove(0);
    EXPECT_EQ(automator->getUnqueuedSize(), 0);
}


TEST(AutomatorTest, testPerformTasks){
    //set up
    DataManager* manager = new DataManager;
    Automator* automator = new Automator(manager);
    QSignalSpy spy(automator, &Automator::sig_progress);
    QDir dir(QDir::current().path());
    dir.cd("tasks");
    automator->addTasks(dir.path() + "/task1.json");
    automator->addTasks(dir.path() + "/task2.json");
    automator->addTasks(dir.path() + "/task3.json");
    automator->queue(2);
    automator->queue(1);
    automator->queue(0);
    QSignalSpy taskStateSpy(automator, &Automator::sig_taskUpdate);

    //start performing
    automator->performTasks();

    //test if expected signals were sent
    EXPECT_EQ(spy.size(), 4);
    EXPECT_EQ(taskStateSpy.size(), 6);
    //progress signals
    EXPECT_EQ(spy.at(0).at(0).toInt(), 33);
    EXPECT_EQ(spy.at(1).at(0).toInt(), 66);
    EXPECT_EQ(spy.at(2).at(0).toInt(), 100);
    EXPECT_EQ(spy.at(3).at(0).toInt(), 100);
    //state signals
    EXPECT_EQ(taskStateSpy.at(0).at(1).toString(), "Performing");
    EXPECT_EQ(taskStateSpy.at(1).at(1).toString(), "Completed");
    EXPECT_EQ(taskStateSpy.at(2).at(1).toString(), "Performing");
    EXPECT_EQ(taskStateSpy.at(3).at(1).toString(), "Completed");
    EXPECT_EQ(taskStateSpy.at(4).at(1).toString(), "Performing");
    EXPECT_EQ(taskStateSpy.at(5).at(1).toString(), "Completed");
}