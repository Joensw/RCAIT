#include "inputimageswidget.h"
#include "ui_inputimageswidget.h"

#include <QFileDialog>


InputImagesWidget::InputImagesWidget(QWidget *parent) :
    QWidget(parent),
    ui(new Ui::InputImagesWidget)
{
    ui->setupUi(this);
    ui->preview->setDragDropEnabled(false);
}

InputImagesWidget::~InputImagesWidget()
{
    delete ui;
}

void InputImagesWidget::slot_progress(int progress)
{
    ui->progressBar->setValue(progress);
}


void InputImagesWidget::on_selectFolderButton_clicked()
{
     path = QFileDialog::getExistingDirectory(this, DIALOG_CAPTION);
     if (path == nullptr) return;
     QStringList imagePaths;
     QDir imgDir(path);
     for (const QString &imgSubPath: imgDir.entryList(QDir::AllDirs | QDir::NoDotAndDotDot)) {
         QDir imgSubDir(path + "/" + imgSubPath);
         for (const QString &imageName: imgSubDir.entryList(QStringList() << "*.JPG" << "*.jpg" << "*.jpeg" << "*.png",
                                                            QDir::Files)) {
             imagePaths.append(imgSubDir.absoluteFilePath(imageName));
         }
     }
     ui->preview->setImageSize((this->width() - 94) / 5);
     ui->preview->clearAndStop();
     ui->preview->setEnabled(true);
     ui->preview->concurrentAddImages(imagePaths);
     ui->classifyButton->setEnabled(true);
}



void InputImagesWidget::on_classifyButton_clicked()
{
    ui->classifyButton->setEnabled(false);
    ui->progressBar->setEnabled(true);
    ui->selectFolderButton->setEnabled(false);
    ui->cancelButton->setEnabled(true);


    emit sig_startClassify(path);
}


void InputImagesWidget::on_cancelButton_clicked()
{
    emit sig_abortClassify();

    ui->classifyButton->setEnabled(true);
    ui->progressBar->setEnabled(true);
    ui->selectFolderButton->setEnabled(true);
    ui->cancelButton->setEnabled(false);
}

void InputImagesWidget::changeEvent(QEvent *event) {
    if (event->type() == QEvent::LanguageChange) {
        // this event is sent if a translator is loaded
        retranslateUi();
        ui->retranslateUi(this);
    }
    //Call to parent class
    QWidget::changeEvent(event);
}




/**
 * Translate and set all the strings which
 * were not created in the UI builder
 */
void InputImagesWidget::retranslateUi() {
    //TODO translate file dialog
}
