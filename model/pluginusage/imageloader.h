#ifndef IMAGELOADER_H
#define IMAGELOADER_H


#include <QStringList>
#include "imagesearchthread.h"

class ImageLoader : public ProgressablePlugin {
    Q_OBJECT
    QThread imageloadThread;
public:
    ImageLoader();
    void loadInputImages(int count, QStringList labels, QString pluginName, QString tempImageDir);
    void load();

    ~ImageLoader() {
        imageloadThread.quit();
        imageloadThread.wait();
    }

private:
    ImageSearchThread *m_worker;


public slots:
    void handleResults();
signals:
    void operate();
    void sig_imagesReady();

};


#endif //IMAGELOADER_H
