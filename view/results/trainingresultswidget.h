#ifndef TRAININGRESULTSWIDGET_H
#define TRAININGRESULTSWIDGET_H

#include <QWidget>
#include <QMenu>
#include <QPushButton>
#include <QRandomGenerator>
#include <accuracycurve.h>
#include <confusionmatrix.h>
#include <projectmanager.h>
#include "topaccuraciesview.h"
#include "trainingresultview.h"

namespace Ui {
    class TrainingResultsWidget;
}

class TrainingResultsWidget : public QWidget {
Q_OBJECT

protected:
    // this event is called, when a new translator is loaded or the system language is changed
    void changeEvent(QEvent *) override;

public:
    explicit TrainingResultsWidget(QWidget *parent = nullptr);

    ~TrainingResultsWidget();

    void addTrainingResult(TrainingResult *result);

    TopAccuraciesView *getTopAccuraciesView();

private:
    Ui::TrainingResultsWidget *ui;
    QPushButton *pushButton_addResult = new QPushButton(this);
    QMenu *menu_addRun = new QMenu(pushButton_addResult);
    QMap<QString, QWidget *> m_mapTrainingResultTabs;

    TrainingResultView *createTrainingResultTab(const QString &tabName);

    void deleteTrainingResultTab(const QString &tabName);

    void retranslateUi();

    void configure_compareRunButton();

    void configure_compareRunMenu();

signals:

    void sig_loadTrainingImagesToCompare(const QString &runNameToCompare, TrainingResultView *view);

    void sig_loadAccuracyDataToCompare(const QString &runNameToCompare, TopAccuraciesView *view);

    void sig_unloadAccuracyDataToCompare(const QString &runNameToCompare, TopAccuraciesView *view);

private slots:

    void slot_comparisonMenu_triggered(QAction *action);
};

#endif // TRAININGRESULTSWIDGET_H
