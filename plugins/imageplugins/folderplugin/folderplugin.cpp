#include "folderconfigwidget.h"
#include "folderplugin.h"


bool FolderPlugin::loadImages(const QString path, ProgressablePlugin* receiver, const int imageCount = 0, const QStringList label = QStringList())
{
    abort = false;
    connect(receiver, &ProgressablePlugin::sig_pluginAborted, this, &FolderPlugin::slot_abort);
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
            foreach (QString folderName, imagefolders){
                if (abort) return false;
                folder.cd(folderName);
                QStringList imagelist = folder.entryList(QStringList() << "*.JPG" << "*.jpg"  << "*.jpeg" << "*.png", QDir::Files);
                if (!imagelist.isEmpty()){
                    if (!addLabel(imagelist, folder, output)){
                        receiver->slot_makeProgress(100);
                        return false;
                    }                   
                }
                receiver->slot_makeProgress((i * 100 + 100) / imagefolders.count());
                i++;
                folder.cdUp();
            }
            receiver->slot_makeProgress(100);
            return true;
            break;
        }

        case 1: {
            // syntax for labels by filename is "label_image.png"
            QStringList images = folder.entryList(QStringList() << "*_*.JPG" << "*_*.jpg" << "*_*.jpeg" << "*_*.png", QDir::Files);
            foreach (QString image, images){
                if (abort) return false;
                QString label = image.mid(0, image.indexOf("_"));
                output.mkdir(label);
                if (!output.cd(label)) {
                    receiver->slot_makeProgress(100);
                    return false;
                }
                QString path = folder.path() + "/" + image;
                QFile::copy(path, output.path() + "/" + image.mid(image.indexOf("_") + 1));
                output.cdUp();
            }
            receiver->slot_makeProgress(100);
            return true;
            break;
        }
        case 2: {
            QStringList images = folder.entryList(QStringList() << "*.JPG" << "*.jpg" << "*.jpeg" << "*.png", QDir::Files);
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

void FolderPlugin::slot_abort()
{
    abort = true;
}

bool FolderPlugin::addLabel(QStringList images, QDir in, QDir out)
{
    out.mkdir(in.dirName());
    if (!out.cd(in.dirName())) return false;
    foreach (QString imageName, images) {
        if (abort) return false;
        QString path = in.path() + "/" + imageName;
        QFile::copy(path, out.path() + "/" + imageName);
    }
    return true;
}
