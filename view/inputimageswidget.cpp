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

void InputImagesWidget::slot_loaded(QString path)
{

}

/*!
 * \brief InputImagesWidget::on_selectFolderButton_clicked
 *
 * Used when selectFolderButton is clicked.
 * Opens a file dialog and loads images of folder in preview.
 */
void InputImagesWidget::on_selectFolderButton_clicked()
{
     path = QFileDialog::getExistingDirectory(this, "Select image directory");
     if (path == nullptr) return;
     ui->preview->setEnabled(true);
     ui->preview->concurrentAddDir(path);
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

