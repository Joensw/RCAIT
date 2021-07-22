#ifndef AITRAININGWIDGET_H
#define AITRAININGWIDGET_H

#include <QWidget>

namespace Ui {
class AITrainingWidget;
}

/**
 * @brief The AITrainingWidget class is a UI for setting parameters and initializing training of classification models
 */
class AITrainingWidget : public QWidget
{
    Q_OBJECT

public:
    /**
     * @brief AITrainingWidget create a new AiTraingWidget
     * @param parent optional parent argument
     */
    explicit AITrainingWidget(QWidget *parent = nullptr);
    ~AITrainingWidget();

    /**
     * @brief getCropSize returns the crop size for data augmentation from the UI
     * @return int value the crop size entered in the UI
     */
    int getCropSize();

    /**
     * @brief getFlipDirection returns the flip direction for the data augmentation from the UI
     * @return  String valuerepresenting flip direction entered in the UI
     */
    QString getFlipDirection();

    /**
     * @brief getNormalizationTable returns the normalization Table for the data augmentation from the UI
     * @return normalization table specified in the UI
     */
    QVector<QPair<double, double>> getNormalizationTable();

    /**
     * @brief getFlipProbability returns the flip probability for the data augmentation from the UI
     * @return double value representing flip probability entered in the UI
     */
    double getFlipProbability();

    /**
     * @brief getResizeValue returns the resize value for the data augmentation from the UI
     * @return int value representating the resize value entered in the UI
     */
    int getResizeValue();


public slots:
    /**
     * @brief slot_progress update the progress bar shown in the UI representing the progress of the training
     * @param progress integer argument 1-100
     */
    void slot_progress(int progress);

signals:
    /**
     * @brief sig_showAugmentationPreview emitted when a preview of the data augmentation is to be shown in the UI
     */
    void sig_showAugmentationPreview();

    /**
     * @brief sig_startTraining emitted when the training is to be started
     */
    void sig_startTraining();

    /**
     * @brief sig_abortTraining emitted when the training is to be aborted
     */
    void sig_abortTraining();

    /**
     * @brief sig_results emitted when the results are to be shown
     */
    void sig_results();

protected:
    void changeEvent(QEvent *event);

private slots:
    //slots correspond with the identically named button in the UI
    void on_startButton_clicked();

    void on_cancelButton_clicked();

    void on_resultsButton_clicked();

    void on_previewButton_clicked();

private:
    Ui::AITrainingWidget *ui;
};

#endif // AITRAININGWIDGET_H
