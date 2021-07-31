#ifndef FOLDERCONFIGWIDGET_H
#define FOLDERCONFIGWIDGET_H

#include <QtWidgets/QWidget>

namespace Ui {
class FolderConfigwidget;
}

class FolderConfigwidget : public QWidget
{
    Q_OBJECT

public:
    explicit FolderConfigwidget(QWidget *parent = nullptr);
    ~FolderConfigwidget();

    int getLoadMode();

    QString getImageFolder();


private slots:
    //void on_pushButton_clicked();

    void on_loadFolderButton_clicked();

private:
    Ui::FolderConfigwidget *ui;
    QString imageFolder;
};

#endif // FOLDERCONFIGWIDGET_H
