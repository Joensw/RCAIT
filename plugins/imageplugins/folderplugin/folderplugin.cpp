#include "folderconfigwidget.h"
#include "folderplugin.h"


bool FolderPlugin::loadImages(const QString path, ProgressablePlugin* receiver, const int imageCount = 0, const QStringList label = QStringList())
{
    QDir output(path);
    QDir folder = QDir(imageDir);
    if (!folder.exists() || !output.exists()){
        receiver->slot_makeProgress(100);
        return false;
    }

    switch(mode){
        case 0: {
            QStringList imagefolders = folder.entryList(QDir::AllDirs | QDir::NoDotAndDotDot);
            int i = 0;
            foreach(QString folderName, imagefolders){
                folder.cd(folderName);
                QStringList imagelist = folder.entryList(QStringList() << "*.JPG" << "*.jpg" << "*.png", QDir::Files);
                if (!imagelist.isEmpty()){
                    if (!addLabel(imagelist, folder, output)){
                        receiver->slot_makeProgress(100);
                        return false;
                    }
                }
                folder.cdUp();
            }
            receiver->slot_makeProgress(100);
            return true;
            break;
        }

        case 1: {
            // syntax for labels by filename is "label_image.png"
            return false;
            break;
        }
        case 2: {
            QStringList images = folder.entryList(QStringList() << "*.JPG" << "*.jpg" << "*.png", QDir::Files);
            bool success = addLabel(images, folder, output);
            receiver->slot_makeProgress(100);
            return success;
            break;
        }

    default: return false;
    }

}

QWidget *FolderPlugin::getConfigurationWidget()
{
    return mConfigWidget;
}

void FolderPlugin::saveConfiguration()
{
    mode = mConfigWidget->getLoadMode();
    imageDir = mConfigWidget->getImageFolder();
}

void FolderPlugin::init()
{
    mConfigWidget = new FolderConfigwidget();
}

QString FolderPlugin::getName()
{
    return "FolderPlugin";
}

QWidget *FolderPlugin::getInputWidget()
{
    return mConfigWidget;
}

bool FolderPlugin::addLabel(QStringList images, QDir in, QDir out)
{
    out.mkdir(in.dirName());
    if(!out.cd(in.dirName())) return false;
    foreach(QString imageName, images) {
        QString path = in.path() + "/" + imageName;
        QFile::copy(path, out.path() + "/" + imageName);
    }
    return true;
}
