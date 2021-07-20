#ifndef RESULTSWIDGET_H
#define RESULTSWIDGET_H


#include <QWidget>
#include <QMenu>
#include <QPushButton>
#include <results/trainingresult.h>
#include <ui_resultswidget.h>
#include "classificationresult.h"
#include "trainingresultview.h"


class ResultsWidget : public QWidget {
Q_OBJECT

protected:
    // this event is called, when a new translator is loaded or the system language is changed
    void changeEvent(QEvent *) override;

public:
    explicit ResultsWidget(QWidget *parent = nullptr);

    ~ResultsWidget();

    QString getSelectedTrainRunIdentifier();

    QString getSelectedClassifyRunIdentifier();

    void addTrainingResult(TrainingResult *result);

    void addClassificationResult(ClassificationResult *result);

    TopAccuraciesView *getTopAccuraciesView();

signals:

    void sig_saveResults();

private:
    Ui::ResultsWidget *ui;
    QPushButton *pushButton_addResult = new QPushButton(this);
    QMenu *menu_addRun = new QMenu(pushButton_addResult);
    QMap<QString, QWidget*> m_mapTrainingResultTabs;

    TrainingResultView *createTrainingResultTab(const QString &tabName);
    void deleteTrainingResultTab(const QString &tabName);

    void dummyFunctionTest();

    void retranslateUi();

    void configure_compareRunButton();

    void configure_compareRunMenu();

private slots:

    void slot_comparisonMenu_triggered(QAction *action);

};


#endif //RESULTSWIDGET_H
