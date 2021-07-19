#ifndef RCAIT_IMAGELOADER_H
#define RCAIT_IMAGELOADER_H


#include <QStringList>
#include "imagesearchthread.h"

class ImageLoader : public ProgressablePlugin {
    Q_OBJECT
    QThread imageloadThread;
public:
    ImageLoader();
    void loadInputImages(int count, QStringList labels, QString pluginName, QString tempImageDir);

    ~ImageLoader() {
        imageloadThread.quit();
        imageloadThread.wait();
    }

public slots:
    void handleResults(const QString &);
signals:
    void operate();
    void sig_imagesReady();
};


#endif //RCAIT_IMAGELOADER_H
