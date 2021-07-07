#ifndef RESULTSWIDGET_H
#define RESULTSWIDGET_H


#include <QWidget>
#include <QMenu>
#include <results/trainingresult.h>
#include <ui_resultswidget.h>
#include "classificationresult.h"
#include "trainingresultview.h"


class ResultsWidget : public QWidget {
Q_OBJECT

public:
    explicit ResultsWidget(QWidget *parent = nullptr);

    ~ResultsWidget();

    QString getSelectedTrainRunIdentifier();

    QString getSelectedClassifyRunIdentifier();

    //Todo: These will probably not just be QImages!
    void addTrainingResult(TrainingResult *result);

    void addClassificationResult(ClassificationResult *result);

signals:

    void sig_saveResults();

private:
    Ui::ResultsWidget *ui;
    QMenu *menu_addRun = new QMenu(this);
    QPushButton *pushButton_addResult = new QPushButton(this);

    void configureAddComparisonButton(QTabWidget *tabWidget);

    TrainingResultView *createTrainingResultTab(const QString &tabName);

    void dummyFunctionTest();

    static QPair<QLineSeries *, QLineSeries *>
    parseLossCurveData(const QMap<int, QPair<double, double>> &data_lossCurve);
};


#endif //RCAIT_RESULTSWIDGET_H
