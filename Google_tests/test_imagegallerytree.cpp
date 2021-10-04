#include <gtest/gtest.h>
#include <QDir>
#include "imagegallerytree.h"
#include <qapplication.h>

class ImageGalleryTreeTest : public testing::Test {
    protected:

    void SetUp() override {
        path = QDir::current().path();
        path += "/test_imagefolder/";
    }

    void TearDown() override {
        QApplication::exit();
    }
    int argc = 1;
    char *argv[1] = {new char('a')};
    QString path;
};

//check if adding labels works
TEST_F(ImageGalleryTreeTest, testAddLabels){
    QApplication a(argc, argv);
    auto tree = QScopedPointer<ImageGalleryTree>(new ImageGalleryTree(nullptr));

    QStringList labels = {"Auto", "Flugzeug"};
    QStringList images = {path + "Auto/images", path + "Auto/images_1", path + "Flugzeug/airliner1", path + "Flugzeug/airliner2"};

    //start adding labels
    tree->addLabels({{labels.at(0), images.mid(0,2)}, {labels.at(1), images.mid(2,2)}});

    using namespace std::chrono_literals;
    std::this_thread::sleep_for(2s);

    //check if imagegalleries have to labels
    EXPECT_EQ(tree->topLevelItemCount(), 2);

    //...and respective imagalleries have items

    ImageGallery *g = static_cast<ImageGallery *> (tree->itemWidget(tree->topLevelItem(0)->child(0),0));
    EXPECT_EQ(g->count(), 2);
    g = static_cast<ImageGallery *> (tree->itemWidget(tree->topLevelItem(1)->child(0),0));
    EXPECT_EQ(g->count(), 2);
}

//check if resetting images from image list works
TEST_F(ImageGalleryTreeTest, testResetTree){
    QApplication a(argc, argv);
    auto tree = QScopedPointer<ImageGalleryTree>(new ImageGalleryTree(nullptr));

    QStringList labels = {"Auto", "Flugzeug"};
    QStringList images = {path + "Auto/images", path + "Auto/images_1", path + "Flugzeug/airliner1", path + "Flugzeug/airliner2"};

    //start adding labels
    tree->addLabels({{labels.at(0), images.mid(0,2)}, {labels.at(1), images.mid(2,2)}});
    //reset tree imageload
    tree->resetTree();

    //check if tree is resetted
    EXPECT_EQ(tree->topLevelItemCount(), 0);
}

//check if removing images works
TEST_F(ImageGalleryTreeTest, testAddPathImages){
    QApplication a(argc, argv);
    auto tree = QScopedPointer<ImageGalleryTree>(new ImageGalleryTree(nullptr));

    QStringList labels = {"Auto", "Flugzeug"};
    QStringList images = {path + "Auto/images", path + "Auto/images_1", path + "Flugzeug/airliner1", path + "Flugzeug/airliner2"};

    //start adding labels
    tree->addLabels({{labels.at(0), images.mid(0,2)}, {labels.at(1), images.mid(2,2)}});

    using namespace std::chrono_literals;
    std::this_thread::sleep_for(2s);

    //check if imagegalleries have to labels
    EXPECT_EQ(tree->topLevelItemCount(), 2);

    //...and top level items are removed if imagallerie is empty
    ImageGallery *g = static_cast<ImageGallery *> (tree->itemWidget(tree->topLevelItem(0)->child(0),0));
    EXPECT_EQ(g->count(), 2);
    g->selectAll();
    tree->removeSelected();
    EXPECT_EQ(tree->topLevelItemCount(), 1);
    EXPECT_EQ(g->count(), 0);
}

