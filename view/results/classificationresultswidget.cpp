#include <projectmanager.h>
#include <QDir>
#include "classificationresultswidget.h"
#include "ui_classificationresultswidget.h"

ClassificationResultsWidget::ClassificationResultsWidget(QWidget *parent) :
        QWidget(parent),
        ui(new Ui::ClassificationResultsWidget) {
    ui->setupUi(this);

    connect(menu_addRun, &QMenu::triggered, this, &ClassificationResultsWidget::slot_comparisonMenu_triggered);

    //TODO Replace dummy (without it, comparison menu won't appear)
    ui->tabWidget_classificationresults->addTab(new QWidget(), "DUMMY");
    configure_compareRunButton();
    configure_compareRunMenu();

}

void ClassificationResultsWidget::configure_compareRunMenu() {
    //Add compare button menu entries
    auto resultsDirPath = ProjectManager::getInstance().getResultsDir();
    auto dir = QDir(resultsDirPath);
    auto entryList = dir.entryList(QDir::AllDirs | QDir::NoDotAndDotDot);

    for (const auto &item : entryList) {
        //Compare Run Button Menu
        auto *action = new QAction(item, menu_addRun);
        action->setCheckable(true);
        menu_addRun->addAction(action);
    }
}

void ClassificationResultsWidget::configure_compareRunButton() {
    //Configure add run compare button
    const auto icon = QIcon(":/Resources/UISymbols/UI_Add_Result_Comparison_Icon.svg");
    pushButton_addResult->setIcon(icon);
    pushButton_addResult->setFlat(true);
    pushButton_addResult->setMenu(menu_addRun);
    ui->tabWidget_classificationresults->setCornerWidget(pushButton_addResult, Qt::TopRightCorner);
}

void ClassificationResultsWidget::addClassificationResult(ClassificationResult *result) {
//TODO: Fill
}

void ClassificationResultsWidget::slot_comparisonMenu_triggered(QAction *action) {
    const QString &runNameToCompare = action->text();
    if (action->isChecked()) {
        auto tab = createClassificationResultTab(runNameToCompare);
        emit sig_loadClassificationDataToCompare(runNameToCompare, tab);
        //TODO Implementation/design of classification results graphic w/ stacked barcharts
        //emit sig_loadClassificationImagesToCompare(runNameToCompare, topAccuracies);
    } else {
        deleteClassificationResultTab(runNameToCompare);
    }
}

void ClassificationResultsWidget::changeEvent(QEvent *event) {
    if (event->type() == QEvent::LanguageChange) {
        // this event is send if a translator is loaded
        retranslateUi();
        ui->retranslateUi(this);
    }
    //Call to parent class
    QWidget::changeEvent(event);
}

/**
 * Translate and set all the strings which
 * were not created in the UI builder
 */
void ClassificationResultsWidget::retranslateUi() {
    pushButton_addResult->setText(tr("Compare ..."));
}

ClassificationResultsWidget::~ClassificationResultsWidget() {
    delete ui;
}

ClassificationResultView *ClassificationResultsWidget::createClassificationResultTab(const QString &tabName) {
    auto *tab = new ClassificationResultView(this);
    ui->tabWidget_classificationresults->addTab(tab, tabName);
    m_mapClassificationResultTabs[tabName] = tab;

    //Forward signals
    connect(tab, &ClassificationResultView::sig_requestClassificationResultGraphics, this, &ClassificationResultsWidget::slot_requestClassificationResultGraphics);
    return tab;
}

void ClassificationResultsWidget::deleteClassificationResultTab(const QString &tabName) {
    auto *tabWidget = ui->tabWidget_classificationresults;
    auto tab = m_mapClassificationResultTabs.take(tabName);
    auto index = tabWidget->indexOf(tab);
    tabWidget->removeTab(index);
}

void ClassificationResultsWidget::slot_requestClassificationResultGraphics(AbstractGraphicsView *receiver) {
    //Forwarded signal
    emit sig_requestClassificationResultGraphics(receiver);
}
