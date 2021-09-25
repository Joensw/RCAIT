/**
 * @file folderplugin.cpp
 *
 * @brief contains method implementations for FolderPlugin class
 */
#include "folderconfigwidget.h"
#include "folderplugin.h"


bool FolderPlugin::loadImages(const QString &path, ProgressablePlugin *receiver, int /*imageCount*/, const QStringList &/*label*/) {
    abort = false;
    connect(receiver, &ProgressablePlugin::sig_pluginAborted, this, &FolderPlugin::slot_abort);
    QDir output(path);
    QDir folder = QDir(imageDir);
    if (!folder.exists() || !output.exists()) {
        receiver->slot_makeProgress(100);
        return false;
    }

    //TODO: Enum for case numbers
    switch (mode) {
        case 0: {
            auto imageFolders = folder.entryList(QDir::AllDirs | QDir::NoDotAndDotDot);
            int i = 0;
            for (const QString &folderName: imageFolders) {
                if (abort) return false;

                folder.cd(folderName);
                auto imageList = folder.entryList({"*.JPG", "*.jpg", "*.jpeg", "*.png"}, QDir::Files);

                if (imageList.isEmpty() || addLabel(imageList, folder, output)) {
                    receiver->slot_makeProgress((int) ((i++ * 100 + 100) / imageFolders.count()));
                    folder.cdUp();
                } else {
                    receiver->slot_makeProgress(100);
                    return false;
                }
            }
            receiver->slot_makeProgress(100);
            return true;
        }

        case 1: {
            // syntax for labels by filename is "label_image.png"
            auto images = folder.entryList({"*_*.JPG", "*_*.jpg", "*_*.jpeg", "*_*.png"}, QDir::Files);

            for (const QString &image: images) {
                if (abort) return false;
                auto label = image.mid(0, image.indexOf("_"));
                output.mkdir(label);

                if (!output.cd(label)) {
                    receiver->slot_makeProgress(100);
                    return false;
                }

                QString target = folder.path() % "/" % image;
                QFile::copy(target, output.path() % "/" % image.mid(image.indexOf("_") + 1));
                output.cdUp();
            }
            receiver->slot_makeProgress(100);
            return true;
        }
        case 2: {
            auto images = folder.entryList({"*.JPG", "*.jpg", "*.jpeg", "*.png"}, QDir::Files);
            bool success = addLabel(images, folder, output);
            receiver->slot_makeProgress(100);
            return success;
        }

        default:
            return false;
    }

}

QSharedPointer<QWidget> FolderPlugin::getConfigurationWidget() {
    return mConfigWidget;
}

void FolderPlugin::saveConfiguration() {
    mode = mConfigWidget->getLoadMode();
    imageDir = mConfigWidget->getImageFolder();
}

void FolderPlugin::init() {
    mConfigWidget.reset(new FolderConfigwidget, &QObject::deleteLater);
}

QString FolderPlugin::getName() {
    return "Folder Loader Plugin";
}

QSharedPointer<QWidget> FolderPlugin::getInputWidget() {
    return mConfigWidget;
}

void FolderPlugin::slot_abort() {
    abort = true;
}

bool FolderPlugin::addLabel(const QStringList &images, const QDir &in, QDir out) const {
    out.mkdir(in.dirName());
    if (!out.cd(in.dirName())) return false;
    return std::all_of(images.begin(), images.end(), [this, &in, &out](const QString &imageName) {
        if (abort) return false;
        QString path = in.path() % "/" % imageName;
        QFile::copy(path, out.path() % "/" % imageName);
        return true;
    });
}
