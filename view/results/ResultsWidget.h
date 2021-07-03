#ifndef RESULTSWIDGET_H
#define RESULTSWIDGET_H


#include <QWidget>
#include <QMenu>
#include <results/TrainingResult.h>
#include <ui_resultswidget.h>
#include "TrainingResultView.h"


class ResultsWidget : public QWidget {
Q_OBJECT

public:
    explicit ResultsWidget(QWidget* parent = nullptr);
    ~ResultsWidget();
    QString getSelectedTrainRunIdentifier();
    QString getSelectedClassifyRunIdentifier();
    //Todo: These will probably not just be QImages!
    void addTrainingResult(TrainingResult* result);
    void addClassificationResult(QList<QImage> result);
    void updateComparisonResultOverview(TrainingResult* trainingResult);
    //Todo: Weird
    void setErrorMessage(QString message);

signals:
    void sig_saveResults();
    //Todo: Check if these are needed
    void sig_startTrainingComparison();
    void sig_startClassificationComparison();

private:
    Ui::ResultsWidget *ui;
    QMenu *menu_addRun = new QMenu(this);
    QPushButton *pushButton_addResult = new QPushButton(this);

    void createAddRunButton(QTabWidget *tabWidget);

    TrainingResultView * createTrainingResultTab(const QString& tabName);
};


#endif //RCAIT_RESULTSWIDGET_H
