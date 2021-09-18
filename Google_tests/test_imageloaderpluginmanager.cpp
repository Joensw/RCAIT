#include "imageloaderpluginmanager.h"
#include "imageloaderpluginmock.h"
#include <gtest/gtest.h>
#include <qapplication.h>


class ImageLoaderPluginManagerTest : public testing::Test {
    protected:


    static void SetUpTestSuite() {



    }

      static void TearDownTestSuite() {

      }

    void SetUp() override {
        int argc;
        char *argv[1];
        QApplication a(argc, argv);
        pluginDir = QDir::current().path();
        testee.loadPlugins(pluginDir);

    }

    void TearDown() override {
        QApplication::exit();
    }

    ImageLoaderPluginManager& testee = ImageLoaderPluginManager::getInstance();
    QString pluginDir;

 };


TEST_F(ImageLoaderPluginManagerTest, testLoadPlugins){
    QStringList pluginNames = testee.getNamesOfPlugins();
    EXPECT_TRUE(!pluginNames.isEmpty());
    EXPECT_TRUE(!QString::compare(pluginNames.at(0), ImageLoaderPluginMock::PLUGIN_NAME));
}

TEST_F(ImageLoaderPluginManagerTest, testCallMethods){

    testee.getConfigurationWidget(ImageLoaderPluginMock::PLUGIN_NAME);
    testee.getInputWidget(ImageLoaderPluginMock::PLUGIN_NAME);
    testee.getConfigurationWidgets();
    testee.saveConfiguration(ImageLoaderPluginMock::PLUGIN_NAME);
    testee.loadImages("",nullptr,ImageLoaderPluginMock::PLUGIN_NAME, 10, QStringList());
    EXPECT_TRUE(true);
}
