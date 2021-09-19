#include <gtest/gtest.h>
#include <QDir>
#include "imagegallery.h"
#include <qapplication.h>

//check if adding image works
TEST(ImageGalleryTest, testAddImage){
    //setup
    int argc = 1;
    char *argv[1] = {new char('a')};
    QApplication a(argc, argv);
    QString path = QDir::current().path();
    path += "/test_imagefolder/Auto/images";
    ImageGallery* gallery = new ImageGallery();

    //start imageload
    gallery->addImage(QImage(path));

    //check if image is loaded
    EXPECT_EQ(gallery->count(), 1);
    EXPECT_TRUE(gallery->item(0)->data(Qt::DecorationRole).isValid());

    //tear down
    a.exit();
}

//check if adding images from image list works
TEST(ImageGalleryTest, testAddImages){
    //setup
    int argc = 1;
    char *argv[1] = {new char('a')};
    QApplication a(argc, argv);
    QString path = QDir::current().path();
    path += "/test_imagefolder/Auto/";
    QList<QImage> imgList;
    imgList.append(QImage(path + "images"));
    imgList.append(QImage(path + "images_1"));
    ImageGallery* gallery = new ImageGallery();

    //start imageload
    gallery->addImages(imgList);

    //check if image is loaded
    EXPECT_EQ(gallery->count(), 2);
    EXPECT_TRUE(gallery->item(0)->data(Qt::DecorationRole).isValid());
    EXPECT_TRUE(gallery->item(1)->data(Qt::DecorationRole).isValid());

    //tear down
    a.exit();
}

//check if adding images from path list works
TEST(ImageGalleryTest, testAddPathImages){
    //setup
    int argc = 1;
    char *argv[1] = {new char('a')};
    QApplication a(argc, argv);
    QString path = QDir::current().path();
    path += "/test_imagefolder/Auto/";
    QList<QString> imgList;
    imgList.append(path + "images");
    imgList.append(path + "images_1");
    ImageGallery* gallery = new ImageGallery();

    //start imageload
    gallery->addImages(imgList);

    //check if image is loaded
    EXPECT_EQ(gallery->count(), 2);
    EXPECT_TRUE(gallery->item(0)->data(Qt::DecorationRole).isValid());
    EXPECT_TRUE(gallery->item(1)->data(Qt::DecorationRole).isValid());

    //tear down
    a.exit();
}

//check if adding images dir works
TEST(ImageGalleryTest, testConcurrentAddDir){
    //setup
    int argc = 1;
    char *argv[1] = {new char('a')};
    QApplication a(argc, argv);
    QString path = QDir::current().path();
    path += "/test_imagefolder/Auto/";
    ImageGallery* gallery = new ImageGallery();

    //start imageload
    gallery->concurrentAddImages(path);

    using namespace std::chrono_literals;
      std::this_thread::sleep_for(2s);

    //check if images are loaded
    EXPECT_EQ(gallery->count(), 2);
    EXPECT_TRUE(gallery->item(0)->data(Qt::DecorationRole).isValid());
    EXPECT_TRUE(gallery->item(1)->data(Qt::DecorationRole).isValid());

    //tear down
    a.exit();
}

//check if stopping load works
TEST(ImageGalleryTest, testStopConcurrentAddImages){
    //setup
    int argc = 1;
    char *argv[1] = {new char('a')};
    QApplication a(argc, argv);
    QString path = QDir::current().path();
    path += "/test_imagefolder/label_names/";
    QList<QString> imgList;
    imgList.append(path + "label1_1");
    imgList.append(path + "label1_2");
    imgList.append(path + "label2_1");
    imgList.append(path + "label2_2");
    imgList.append(path + "label3_1");
    imgList.append(path + "label3_2");
    ImageGallery* gallery = new ImageGallery();

    //start imageload
    gallery->concurrentAddImages(imgList);
    emit gallery->sig_stopLoading();


    //check if imageloading was stopped
    EXPECT_TRUE(gallery->count() < 6);

    //tear down
    using namespace std::chrono_literals;
    std::this_thread::sleep_for(2s);
    a.exit();
}

//check if clear and stop works
TEST(ImageGalleryTest, testClearAndStop){
    //setup
    int argc = 1;
    char *argv[1] = {new char('a')};
    QApplication a(argc, argv);
    QString path = QDir::current().path();
    path += "/test_imagefolder/Auto/";
    QList<QImage> imgList;
    imgList.append(QImage(path + "images"));
    imgList.append(QImage(path + "images_1"));
    ImageGallery* gallery = new ImageGallery();

    //start imageload
    gallery->concurrentAddImages(imgList);
    gallery->clearAndStop();


    //check if imageloading was stopped and gallery cleared
    EXPECT_TRUE(gallery->count() == 0);

    //tear down
    using namespace std::chrono_literals;
    std::this_thread::sleep_for(1ms);
    a.exit();
}
