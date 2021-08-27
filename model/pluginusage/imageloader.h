#ifndef IMAGELOADER_H
#define IMAGELOADER_H


#include <QStringList>
#include <imageloaderpluginmanager.h>

class ImageLoader : public ProgressablePlugin {
    Q_OBJECT
public:
    ImageLoader();
    void loadInputImages(int count, QStringList labels, QString pluginName, QString tempImageDir);


private:
    ImageLoaderPluginManager& mManager = ImageLoaderPluginManager::getInstance();


public slots:
    void handleResults();
    void slot_makeProgress(int progress) override;


signals:
    void sig_imagesReady();

};


#endif //IMAGELOADER_H
