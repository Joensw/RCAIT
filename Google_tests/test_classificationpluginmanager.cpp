#include "classificationpluginmanager.h"
#include "classificationpluginmock.h"
#include <gtest/gtest.h>
#include <QApplication>

class ClassificationPluginManagerTest : public testing::Test {
    protected:


    static void SetUpTestSuite() {



    }

      static void TearDownTestSuite() {

      }

    void SetUp() override {

        pluginDir = QDir::current().path();


    }

    void TearDown() override {

    }


    QString pluginDir;

 };


TEST_F(ClassificationPluginManagerTest, testLoadPlugins){
    int argc = 0;
    char *argv[1] = {0};
    QApplication a(argc, argv);
    ClassificationPluginManager& testee = ClassificationPluginManager::getInstance();
    testee.loadPlugins(pluginDir);
    QStringList pluginNames = testee.getNamesOfPlugins();
    EXPECT_TRUE(!pluginNames.isEmpty());
    EXPECT_TRUE(!QString::compare(pluginNames.at(0), ClassificationPluginMock::PLUGIN_NAME));
    QApplication::exit();
}

TEST_F(ClassificationPluginManagerTest, testCallMethodsWithPluginLoaded){
    int argc = 0;
    char *argv[1] = {0};
    QApplication a(argc, argv);
    ClassificationPluginManager& testee = ClassificationPluginManager::getInstance();
    testee.loadPlugins(pluginDir);
    testee.getConfigurationWidget(ClassificationPluginMock::PLUGIN_NAME);
    testee.getInputWidget(ClassificationPluginMock::PLUGIN_NAME);
    testee.getConfigurationWidgets();
    testee.saveConfiguration(ClassificationPluginMock::PLUGIN_NAME);
    testee.getDataAugmentationInputWidget(ClassificationPluginMock::PLUGIN_NAME);
    testee.createNewModel(ClassificationPluginMock::PLUGIN_NAME,"","");
    testee.getAugmentationPreview(ClassificationPluginMock::PLUGIN_NAME,"","","",10);
    testee.removeModel(ClassificationPluginMock::PLUGIN_NAME,"");

    EXPECT_TRUE(true);
    QApplication::exit();
}

TEST_F(ClassificationPluginManagerTest, testCallMethodsWithOutPluginLoaded){
    int argc = 0;
    char *argv[1] = {0};
    QApplication a(argc, argv);
    ClassificationPluginManager& testee = ClassificationPluginManager::getInstance();
    testee.loadPlugins(pluginDir + "/dataset");
    testee.getConfigurationWidget(ClassificationPluginMock::PLUGIN_NAME);
    testee.getInputWidget(ClassificationPluginMock::PLUGIN_NAME);
    testee.getConfigurationWidgets();
    testee.saveConfiguration(ClassificationPluginMock::PLUGIN_NAME);
    testee.getDataAugmentationInputWidget(ClassificationPluginMock::PLUGIN_NAME);
    testee.createNewModel(ClassificationPluginMock::PLUGIN_NAME,"","");
    testee.getAugmentationPreview(ClassificationPluginMock::PLUGIN_NAME,"","","",10);
    testee.removeModel(ClassificationPluginMock::PLUGIN_NAME,"");

    EXPECT_TRUE(true);
    QApplication::exit();
}
