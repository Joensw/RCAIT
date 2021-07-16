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

protected:
    // this event is called, when a new translator is loaded or the system language is changed
    void changeEvent(QEvent *) override;

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
    QPushButton *pushButton_addResult = new QPushButton(this);
    QMenu *menu_addRun = new QMenu(pushButton_addResult);
    QMap<QString, QWidget*> m_mapTrainingResultTabs;

    TrainingResultView *addTrainingResultTab(const QString &tabName);

    void dummyFunctionTest();

    void retranslateUi();

private slots:

    void slot_comparisonMenu_triggered(QAction *action);

    void deleteTrainingResultTab(const QString &tabName);
};


#endif //RESULTSWIDGET_H
