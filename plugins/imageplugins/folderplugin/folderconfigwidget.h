#ifndef FOLDERCONFIGWIDGET_H
#define FOLDERCONFIGWIDGET_H

#include <QtWidgets/QWidget>

namespace Ui {
class FolderConfigwidget;
}

class FolderConfigwidget : public QWidget
{
    Q_OBJECT
    Q_PROPERTY(QString imageFolder READ getImageFolder WRITE setImageFolder);
    Q_PROPERTY(int loadMode READ getLoadMode WRITE setLoadMode);

public:
    explicit FolderConfigwidget(QWidget *parent = nullptr);
    ~FolderConfigwidget();

    int getLoadMode();

    void setLoadMode(int mode);

    QString getImageFolder();

    void setImageFolder(QString folder);


private slots:
    void on_loadFolderButton_clicked();

    void on_comboBox_currentIndexChanged(int index);

private:
    Ui::FolderConfigwidget *ui;
    QString imageFolder;
    int loadMode;
};

#endif // FOLDERCONFIGWIDGET_H
