/**
 * @file folderconfigwidget.h
 *
 * @brief contains the FolderConfigWidget class
 */
#ifndef FOLDERCONFIGWIDGET_H
#define FOLDERCONFIGWIDGET_H

#include <QtWidgets/QWidget>
#include <QtWidgets/QFileDialog>

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

protected:

    /**
     * @brief changeEvent event handler
     *
     * @param event incoming event
     */
    void changeEvent(QEvent *event) override;

public:

    /**
     * @brief FolderConfigwidget constructs a new config widget.
     *
     * @param parent optional parent widget
     */
    explicit FolderConfigwidget(QWidget *parent = nullptr);

    /**
     * @brief Destructor of this class.
     */
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
    void setImageFolder(const QString &folder);


private slots:
    void on_loadFolderButton_clicked();

    void on_comboBox_currentIndexChanged(int index);

private:
    Ui::FolderConfigwidget *ui;
    QString imageFolder;
    int loadMode;

    static constexpr auto STYLESHEET_GREEN = "QLabel { color : green; }";
    static constexpr auto STYLESHEET_BLUE = "QLabel { color : blue; }";
    static constexpr auto SAVE_SUCESS = QT_TR_NOOP("Saved changes.");
    static constexpr auto UNSAVED_CHANGES = QT_TR_NOOP("There may be unsaved changes.");
    static constexpr auto IMAGE_DIR_SELECT_MSG = QT_TR_NOOP("Select project directory");
};

#endif // FOLDERCONFIGWIDGET_H
