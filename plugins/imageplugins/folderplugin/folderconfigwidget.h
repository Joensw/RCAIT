#ifndef FOLDERCONFIGWIDGET_H
#define FOLDERCONFIGWIDGET_H

#include <QtWidgets/QWidget>

namespace Ui {
class FolderConfigwidget;
}

/**
 * @brief The FolderConfigwidget class is the settings widget of the FolderPlugin.
 *
 */
class FolderConfigwidget : public QWidget
{
    Q_OBJECT
    Q_PROPERTY(QString imageFolder READ getImageFolder WRITE setImageFolder);
    Q_PROPERTY(int loadMode READ getLoadMode WRITE setLoadMode);

public:

    /**
     * @brief FolderConfigwidget constructs a new config widget.
     *
     * @param parent optional parent widget
     */
    explicit FolderConfigwidget(QWidget *parent = nullptr);

    ~FolderConfigwidget();

    /**
     * @brief getLoadMode gets load mode.
     *
     * @return load mode
     */
    int getLoadMode();

    /**
     * @brief setLoadMode sets load mode.
     *
     * @param mode new load mode.
     */
    void setLoadMode(int mode);

    /**
     * @brief getImageFolder gets source image folder.
     *
     * @return image folder path
     */
    QString getImageFolder();

    /**
     * @brief setImageFolder sets source image folder.
     *
     * @param folder new source image folder path
     */
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
