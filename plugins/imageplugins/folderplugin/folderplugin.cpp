#include "folderconfigwidget.h"
#include "folderplugin.h"


bool FolderPlugin::loadImages(const QString path, ProgressablePlugin* receiver, const int imageCount = 0, const QStringList label = QStringList())
{
    QDir output(path);
    QDir folder = QDir(mConfigWidget->getImageFolder());
    if (!folder.exists() || !output.exists()) return false;

    switch(mode){
        case 0: {
            QStringList imagefolders = folder.entryList(QDir::Dirs);
            int i = 0;
            foreach(QString folderName, imagefolders){
                if (folderName == "." || folderName == "..") continue;
                folder.cd(folderName);
                QStringList imagelist = folder.entryList(QStringList() << "*.JPG" << "*.jpg" << "*.png", QDir::Files);
                if (!imagelist.isEmpty()){
                    if (!addLabel(imagelist, folder, output)) return false;
                }
                folder.cdUp();
            }
            return true;
            break;
        }

        case 1: {
            return false;
            break;
        }
        case 2: {
            QStringList images = folder.entryList(QStringList() << "*.JPG" << "*.jpg" << "*.png", QDir::Files);
            return addLabel(images, folder, output);
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
    return new QWidget();
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
