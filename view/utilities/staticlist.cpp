#include "staticlist.h"
#include "ui_staticlist.h"

#include <QDir>
#include <random>


//Lässt sich in der Praxis mit extra Konstruktor von ImageGallery umsetzen
StaticList::StaticList(QWidget *parent) :
    QWidget(parent),
    ui(new Ui::StaticList)
{
    ui->setupUi(this);
    ui->listWidget->setViewMode(QListWidget::ViewMode::IconMode);
    ui->listWidget->setDragEnabled(false);
    ui->listWidget->setSelectionMode(QListWidget::NoSelection);
    ui->listWidget->setResizeMode(QListWidget::Adjust);
    QStringList images = QDir(":/Resources/images/Flugzeug/").entryList(QStringList() << "*.JPG" << "*.jpg" << "*.png", QDir::Files);
    std::shuffle(images.begin(),images.end()-1, std::mt19937(std::random_device()()));
    int i = 0;
    foreach(QString imageName, images){
        if(i >= 10) break;

        QString path = ":/Resources/images/Flugzeug/" + imageName;


        QImage image(path);

       int squareSize = image.height() < image.width() ? image.height() : image.width();
       int leftX = image.width()/2 - squareSize/2;
       int leftY = image.height()/2 - squareSize/2;


        QImage copy = image.copy( leftX, leftY, squareSize, squareSize);
        auto* item = new QListWidgetItem();
        QPixmap tempImage = QPixmap::fromImage(copy);
        item->setData(Qt::DecorationRole, tempImage.scaled(100,100,Qt::KeepAspectRatio));

        ui->listWidget->addItem(item);
        i++;
    }
}

StaticList::~StaticList()
{
    delete ui;
}
