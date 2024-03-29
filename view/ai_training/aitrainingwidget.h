#ifndef AITRAININGWIDGET_H
#define AITRAININGWIDGET_H

#include <QWidget>

namespace Ui {
    class AITrainingWidget;
}

/**
 * @brief The AITrainingWidget class is a UI for setting parameters and initializing training of classification models
 */
class AITrainingWidget : public QWidget {
Q_OBJECT

public:
    /**
     * @brief AITrainingWidget create a new AiTraingWidget
     * @param parent optional parent argument
     */
    explicit AITrainingWidget(QWidget *parent = nullptr);

    /**
     * @brief destructor
     */
    ~AITrainingWidget() override;

    /**
     * @brief setDataAugWidget replace the current widget in the Data augmentation group with the one given
     */

    void setDataAugWidget(const QSharedPointer<QWidget> &replacement);

    /**
     * @brief setAIConfigWidget replace the current widget in the configuration group with the one given
     */

    void setAIConfigWidget(const QSharedPointer<QWidget> &replacement);

    /**
     * @brief showImages update Augmentation Preview tab with images from folder
     * @param path path to folder with images
     */

    void showImages(const QString &path);

public slots:

    /**
     * @brief slot_progress update the progress bar shown in the UI representing the progress of the training
     * @param progress integer argument 1-100
     */
    void slot_progress(const int &progress);

signals:

    /**
     * @brief sig_showAugmentationPreview emitted when a preview of the data augmentation is to be shown in the UI
     */
    void sig_showAugmentationPreview(int amount);

    /**
     * @brief sig_startTraining emitted when the training is to be started
     */
    void sig_startTraining();

    /**
     * @brief sig_abortTraining emitted when the training is to be aborted
     */
    void sig_abortTraining();



protected:

    /**
     * @brief changeEvent event handler
     *
     * @param event incoming event
     */
    void changeEvent(QEvent *event) override;

private slots:

    //slots correspond with the identically named button in the UI
    [[maybe_unused]] void on_startButton_clicked();

    [[maybe_unused]]void on_previewButton_clicked();

private:
    Ui::AITrainingWidget *ui;
};

#endif // AITRAININGWIDGET_H
