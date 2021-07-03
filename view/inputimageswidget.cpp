#include "inputimageswidget.h"
#include "ui_inputimageswidget.h"

#include <QFileDialog>


InputImagesWidget::InputImagesWidget(QWidget *parent) :
    QWidget(parent),
    ui(new Ui::InputImagesWidget)
{
    ui->setupUi(this);
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
     loadDir(QDir(path));
     ui->classifyButton->setEnabled(true);
}



void InputImagesWidget::loadDir(const QDir& imageDirectory) {
    QStringList images = imageDirectory.entryList(QStringList() << "*.JPG" << "*.jpg" << "*.png", QDir::Files);


            foreach(QString imageName, images) {

            QString path = imageDirectory.path() + "/" + imageName;

            QImage image(path);

            int squareSize = image.height() < image.width() ? image.height() : image.width();
            int leftX = image.width() / 2 - squareSize / 2;
            int leftY = image.height() / 2 - squareSize / 2;


            QImage copy = image.copy(leftX, leftY, squareSize, squareSize);
            QListWidgetItem *item = new QListWidgetItem();
            QPixmap tempImage = QPixmap::fromImage(copy);
            item->setData(Qt::DecorationRole, tempImage.scaled(200, 200, Qt::KeepAspectRatio));


            ui->preview->addItem(item);
        }
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

