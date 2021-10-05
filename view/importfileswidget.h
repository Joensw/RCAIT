/**
 * @file importfileswidget.h
 *
 * @brief contains ImportFilesWidget class
 */
#ifndef IMPORTFILESWIDGET_H
#define IMPORTFILESWIDGET_H

#include <QWidget>
#include <QStringBuilder>
#include <QFileDialog>

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

    /**
     * @brief changeEvent event handler
     *
     * @param event incoming event
     */
    void changeEvent(QEvent *) override;

public:
    /**
     * @brief ImportFilesWidget create a new ImportFilesWidget
     * @param parent optional parent argument
     */
    explicit ImportFilesWidget(QWidget *parent = nullptr);

    /**
     * @brief destructor
     */
    ~ImportFilesWidget() override;

    /**
     * @brief setAvailablePlugins sets the image loader plugins present in the UI
     * @param pluginNames the image loader plugin to be shown in the UI
     */
    void setAvailablePlugins(const QStringList &pluginNames);

    /**
     * @brief updateProgressBar updates the status of the progress bar in the UI
     * @param progress integer argument from 1-100 representing the progress in %
     */
    void updateProgressBar(const int &progress);

    /**
     * @brief updateStatusText sets the Text of the label above the statusbar to the input text
     * @param status the text to set
     */
    void updateStatusText(const QString &status);

    /**
     * @brief addModels adds a list of model names to the corresponding view element
     * @param modelNames a list of model names
     */
    void addModels(const QStringList &modelNames);

    /**
     * @brief addNewModel adds a new model to the corresponding view element
     * @param modelName the name of the model to identify it
     */
    void addNewModel(const QString &modelName);

    /**
     * @brief deletes the current list of model names
     */
    void clearModelList();

    /**
     * @brief setLoadButtonEnabled disables or enables the state of the model action bar (remove, open)
     * @param state true to enabled, false to disable
     */
    void setActionButtonsEnabled(const bool &state);

private:
    static constexpr auto DIALOG_CAPTION = QT_TR_NOOP("Select .txt file");

    Ui::ImportFilesWidget *ui;

private slots:

    //slots correspond with the identically named button in the UI
    [[maybe_unused]] void on_pushButton_clearTags_clicked();

    [[maybe_unused]] void on_pushButton_addModel_clicked();

    [[maybe_unused]] void on_pushButton_removeModel_clicked();

    [[maybe_unused]] void on_pushButton_loadModel_clicked();

    [[maybe_unused]] void on_pushButton_loadImages_clicked();

    [[maybe_unused]] void on_horizontalSlider_valueChanged(const int &value);


    [[maybe_unused]] void on_pushButton_loadLabelsFromFile_clicked();

    [[maybe_unused]] void on_pushButton_abortLoading_clicked();

    void slot_setEnableActionButtons();

    void on_horizontalSlider_sliderReleased();

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

    /**
     * @brief sig_abortLoading emits request to abort image loading
     */
    void sig_abortLoading();

    /**
     * @brief sig_splitSliderChanged emits a signal if the slider value is changed
     */
    void sig_splitSliderChanged(int value);
};

#endif // IMPORTFILESWIDGET_H
