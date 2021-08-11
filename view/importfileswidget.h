#ifndef IMPORTFILESWIDGET_H
#define IMPORTFILESWIDGET_H

#include <QWidget>
#include <QValidator>
#include <QFontMetricsF>

namespace Ui {
class ImportFilesWidget;
}
/**
 * @brief The ImportFilesWidget class is UI for loading pictures and models
 */
class ImportFilesWidget : public QWidget
{
    Q_OBJECT

protected:
    // this event is called, when a new translator is loaded or the system language is changed
    void changeEvent(QEvent *) override;

public:
    /**
     * @brief ImportFilesWidget create a new ImportFilesWidget
     * @param parent optional parent arguement
     */
    explicit ImportFilesWidget(QWidget *parent = nullptr);
    ~ImportFilesWidget();

    /**
     * @brief setAvailablePlugins sets the image loader plugins present in the UI
     * @param pluginNames the image loader plugin to be shown in the UI
     */
    void setAvailablePlugins(QStringList pluginNames);

    /**
     * @brief updateProgressBar updates the status of the progress bar in the UI
     * @param progress integer argument from 1-100 representing the progress in %
     */
    void updateProgressBar(int progress);

    /**
     * @brief updateStatusText sets the Text of the label above the statusbar to the input text
     * @param status the text to set
     */
    void updateStatusText(QString status);

private:
    Ui::ImportFilesWidget *ui;


    void retranslateUi();

private slots:
    //slots correspond with the identically named button in the UI
    void on_pushButton_clearTags_clicked();

    void on_pushButton_addModel_clicked();
    void on_pushButton_removeModel_clicked();
    void on_pushButton_loadModel_clicked();

    void on_pushButton_loadImages_clicked();
    void on_horizontalSlider_sliderMoved(int position);


signals:
    /**
     * @brief sig_newModel emitted when the UI to create a new model is to be opened
     */
    void sig_newModel();

    /**
     * @brief sig_removeModel emitted when the UI to remove a model is to be opened
     * @param modelName name of the model to be removed
     */
    void sig_removeModel(QString modelName);

    /**
     * @brief sig_loadModel emitted when a selected is to be loaded as the current model
     * @param modelName name of the model to be loaded
     */
    void sig_loadModel(QString modelName);

    /**
     * @brief sig_loadInputImages emitted when images are to be loaded by a plugin according to the parameters
     * @param pluginName name of the plugin being used
     * @param count amount of images
     * @param label list of keywords representing the search queries
     * @param split integer argument from 1-100
     */
    void sig_loadInputImages(QString pluginName, int count, QStringList label,int split);
};

#endif // IMPORTFILESWIDGET_H
