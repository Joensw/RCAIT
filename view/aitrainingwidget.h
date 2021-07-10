#ifndef AITRAININGWIDGET_H
#define AITRAININGWIDGET_H

#include <QWidget>

namespace Ui {
class AITrainingWidget;
}

class AITrainingWidget : public QWidget
{
    Q_OBJECT

public:
    explicit AITrainingWidget(QWidget *parent = nullptr);
    ~AITrainingWidget();

    int getCropSize();
    QString getFlipDirection();
    QVector<QPair<double, double>> getNormalizationTable();
    double getFlipProbability();
    int getResizeValue();


public slots:
    void slot_progress(int progress);

signals:
    void sig_showAugmentationPreview();
    void sig_startTraining();
    void sig_abortTraining();
    void sig_results();

protected:
    void changeEvent(QEvent *event);

private slots:
    void on_startButton_clicked();

    void on_cancelButton_clicked();

    void on_resultsButton_clicked();

    void on_previewButton_clicked();

private:
    Ui::AITrainingWidget *ui;
};

#endif // AITRAININGWIDGET_H
