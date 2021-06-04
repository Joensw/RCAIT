#ifndef FLICKRSETTINGS_H
#define FLICKRSETTINGS_H

#include <QWidget>
#include <QSettings>
#include <QtCore>

namespace Ui {
class FlickrSettings;
}

class FlickrSettings : public QWidget
{
    Q_OBJECT

public:
    explicit FlickrSettings(QWidget *parent = nullptr);
    ~FlickrSettings();
    void saveSettings();
    void loadSettings();


private:
    Ui::FlickrSettings *ui;
};

#endif // FLICKRSETTINGS_H
