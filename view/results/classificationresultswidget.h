#ifndef CLASSIFICATIONRESULTSWIDGET_H
#define CLASSIFICATIONRESULTSWIDGET_H

#include <QWidget>
#include <QPushButton>
#include <QMenu>
#include <classificationresult.h>
#include "classificationresultview.h"

namespace Ui {
    class ClassificationResultsWidget;
}

class ClassificationResultsWidget : public QWidget {
Q_OBJECT

protected:
    // this event is called, when a new translator is loaded or the system language is changed
    void changeEvent(QEvent *) override;

public:
    explicit ClassificationResultsWidget(QWidget *parent = nullptr);

    ~ClassificationResultsWidget();

    void addClassificationResult(ClassificationResult *result);

private:
    Ui::ClassificationResultsWidget *ui;
    QPushButton *pushButton_addResult = new QPushButton(this);
    QMenu *menu_addRun = new QMenu(pushButton_addResult);
    QMap<QString, QWidget *> m_mapClassificationResultTabs;

    void configure_compareRunButton();

    void configure_compareRunMenu(const QString& resultsDirPath);

    void retranslateUi();

    ClassificationResultView *createClassificationResultTab(const QString &tabName);

    void deleteClassificationResultTab(const QString &tabName);

    void addComparisonResult(const QString &runNameToCompare);

    void removeComparisonResult(const QString &runNameToCompare);

private slots:

    void slot_comparisonMenu_triggered(QAction *action);

    void slot_updateSaveButton(int index);

public slots:

    void slot_updateResultFolderPaths(const QString &trainingResultsPath, const QString &classificationResultsPath);

signals:

    void sig_comparison_loadClassificationResultData(const QString &runNameToCompare, ClassificationResultView *view);

    void sig_comparison_loadClassificationResultGraphics(const QString &runNameToCompare,
                                                         ClassificationResultView *view);

    void sig_normal_loadClassificationData(ClassificationResultView *view, ClassificationResult *result);

    void sig_normal_generateClassificationResultGraphics(AbstractGraphicsView *receiver, ClassificationResult *result);
};

#endif // CLASSIFICATIONRESULTSWIDGET_H
