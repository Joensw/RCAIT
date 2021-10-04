#include <gtest/gtest.h>
#include <QDir>
#include <QSignalSpy>
#include <qapplication.h>
#include <trainer.h>
#include <classificationpluginmock.h>
#include <datamanager.h>

class TrainerTest : public testing::Test {
    protected:

    void SetUp() override {
        QString path = QDir::current().path();
        auto* mngr = &DataManager::getInstance();
        mngr->saveClassificationPluginDir(path);
    }

    //delete testfiles
    void TearDown() override {
        QApplication::exit();
    }
    int argc = 1;
    char *argv[1] = {new char('a')};
};

//check if trainer works with correct training
TEST_F(TrainerTest, testTraining){
    QApplication a(argc, argv);
    //construct trainer
    auto trnr = QScopedPointer<Trainer>(new Trainer);
    QSignalSpy spy(&*trnr, &Trainer::sig_trainingResultUpdated);

    //start training
    trnr->train(ClassificationPluginMock::PLUGIN_NAME, "true", "true", "true", "true");
    using namespace std::chrono_literals;
    std::this_thread::sleep_for(2ms);

    //check if trainingresults are sent
    trnr->slot_handleTrainingsResult();
    EXPECT_EQ(spy.size(), 1);
}

//check if trainer works with incorrect training
TEST_F(TrainerTest, testTrainingFailed) {
    QApplication a(argc, argv);
    //construct trainer
    auto trnr = QScopedPointer<Trainer>(new Trainer);
    QSignalSpy spy(&*trnr, &Trainer::sig_trainingResultUpdated);
    QSignalSpy spyProgress(&*trnr, &Trainer::sig_progress);

    //start training
    trnr->train(ClassificationPluginMock::PLUGIN_NAME, "", "", "", "");
    using namespace std::chrono_literals;
    std::this_thread::sleep_for(2ms);

    //check if no trainingresults are sent
    trnr->slot_handleTrainingsResult();
    EXPECT_EQ(spy.size(), 0);
    //and progress is reported nonetheless
    EXPECT_EQ(spyProgress.size(), 2);
    EXPECT_EQ(spyProgress.at(1).at(0).toInt(), 100);
}

//check if trainer works with data augmentation
TEST_F(TrainerTest, testAugmentation) {
    QApplication a(argc, argv);
    //construct trainer
    auto trnr = QScopedPointer<Trainer>(new Trainer);
    QSignalSpy spy(&*trnr, &Trainer::sig_augmentationPreviewReady);

    //start augmentation preview
    trnr->getAugmentationPreview(ClassificationPluginMock::PLUGIN_NAME, "", "", "", 10);
    using namespace std::chrono_literals;
    std::this_thread::sleep_for(2ms);

    //check if no trainingresults are sent
    trnr->slot_handleAugmentationResult();
    EXPECT_EQ(spy.size(), 1);
    EXPECT_TRUE(spy.at(0).at(0).toBool());
}
