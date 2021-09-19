#include <gtest/gtest.h>
#include <QDir>
#include <QSignalSpy>
#include <qapplication.h>
#include <imageloader.h>
#include <imageloaderpluginmock.h>
#include <datamanager.h>

//check if imageLoader works
TEST(ImageLoaderTest, testImageLoad){
    //setup
    int argc;
    char *argv[1];
    QApplication a(argc, argv);
    QString path = QDir::current().path();
    auto* mngr = &DataManager::getInstance();
    mngr->saveImageLoaderPluginDir(path);


    //construct imageLoader
    ImageLoader* imgld = new ImageLoader;
    QSignalSpy spy(imgld, &ImageLoader::sig_imagesReady);

    //start image loading
    imgld->loadInputImages(1, {}, ImageLoaderPluginMock::PLUGIN_NAME, "");
    using namespace std::chrono_literals;
    std::this_thread::sleep_for(2ms);

    //check if ready signal is sent
    imgld->slot_handleResults();
    EXPECT_EQ(spy.size(), 1);

    //tear down
    QApplication::exit();
}
