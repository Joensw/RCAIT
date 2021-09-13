#include "testgui.h"


void TestGui::testImportFilesWidget()
{

    QString model1 = "model1";
    QString model2 = "model2";
    QStringList models = {model1, model2};

    //create an importfileswidget
    ImportFilesWidget importFilesWidget;
    //add models to it
    importFilesWidget.addModels(models);
    //get the model list widget
    CustomListWidget* list = importFilesWidget.findChild<CustomListWidget*>("listWidget_modelNames");


    QLineEdit lineEdit;

    //loop over items in listwidget and check if the added ones are there
    for(int i = 0; i < list->count(); ++i)
    {
        QListWidgetItem* item = list->item(i);
        qDebug() << "item text is " << item->text();
        QVERIFY(models.contains(item->text()));
        list->setCurrentItem(item);
    }

    QTest::keyClicks(&lineEdit, "hello world");

    QCOMPARE(lineEdit.text(), QString("hello world"));


    //get some buttons for testing
    QPushButton* pushButton_addModel = importFilesWidget.findChild<QPushButton*>("pushButton_addModel");
    QPushButton* pushButton_loadModel = importFilesWidget.findChild<QPushButton*>("pushButton_loadModel");
    QPushButton* pushButton_removeModel = importFilesWidget.findChild<QPushButton*>("pushButton_removeModel");
    QPushButton* pushButton_loadImages = importFilesWidget.findChild<QPushButton*>("pushButton_loadImages");


    list->setCurrentRow(1);
    //remove model cannot be tested properly because the remove dialog for confirmation is opened with a not connected signal in the model (not connected for this test)
    QTest::mouseClick(pushButton_removeModel,Qt::LeftButton);
    list->clear();
    QCOMPARE(list->count(),0);


}

//tests adding and removing tags to the field from the GUI
void TestGui::testTagField()
{
    ImportFilesWidget importFilesWidget;
    Tags* tagfield = importFilesWidget.findChild<Tags*>("lineEdit_labels");

    QString tag1 = "hello world";
    QString tag2 = "Schau mal ne Katze, PSE PSE PSE!";

    QTest::keyClicks(tagfield, tag1);
    QTest::keyPress(tagfield, Qt::Key_Enter, Qt::NoModifier);
    QTest::keyClicks(tagfield, tag2);



    std::vector<QString> tags = tagfield->tags();

    foreach (auto tag, tags) {
        QVERIFY(tag == tag1 || tag == tag2);
        qDebug() << "tag is " << tag;
    }


    QPushButton* pushButton_clearTags = importFilesWidget.findChild<QPushButton*>("pushButton_clearTags");
    QTest::mouseClick(pushButton_clearTags,Qt::LeftButton);

    tags = tagfield->tags();
    QVERIFY(tags.size()==0);


}


QTEST_MAIN(TestGui);
