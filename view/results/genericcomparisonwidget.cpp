#include "genericcomparisonwidget.h"
#include "ui_genericcomparisonwidget.h"


GenericComparisonWidget::GenericComparisonWidget(QWidget *parent)
        : SavableResultsWidget(parent),
          ui(new Ui::GenericComparisonWidget) {

    ui->setupUi(this);

    //Setup variables
    m_tabWidget = ui->tabWidget_compareResults;
    m_pushButton_saveCurrentTab = ui->pushButton_saveCurrentTab;
    m_pushButton_addComparison = new QPushButton(this);
    m_menu_addComparison = new PopupMenu(m_pushButton_addComparison);


    //Connect internal signals and slots
    connect(m_menu_addComparison, &QMenu::triggered, this,
            &GenericComparisonWidget::slot_comparisonMenu_triggered);
    connect(m_tabWidget, &QTabWidget::currentChanged, this,
            &GenericComparisonWidget::slot_updateSaveButton);

    configure_comparisonButton();
}

GenericComparisonWidget::~GenericComparisonWidget() {
    delete ui;
}

void GenericComparisonWidget::configure_comparisonButton() {
    //Configure add run compare button
    const auto icon = QIcon(":/UISymbols/UI_Add_Result_Comparison_Icon.svg");
    m_pushButton_addComparison->setIcon(icon);
    m_pushButton_addComparison->setFlat(true);
    m_pushButton_addComparison->setMenu(m_menu_addComparison);

    m_tabWidget->setCornerWidget(m_pushButton_addComparison, Qt::TopRightCorner);
}

void GenericComparisonWidget::configure_comparisonMenu(const QString &targetDir) {

    QFont inter("Inter Monospace", 9);
    m_menu_addComparison->setFont(inter);

    auto oldMenuEntries = QStringList();
    for (const auto &item : m_menu_addComparison->actions()) {
        oldMenuEntries << item->text();
    }
    //Add new compare button menu entries
    auto dir = QDir(targetDir);
    auto entryList = dir.entryList(QDir::AllDirs | QDir::NoDotAndDotDot);

    for (const auto &item : entryList) {
        auto niceItem = Result::niceRepresentation(item);
        //Leave already contained entries in the menu
        if (oldMenuEntries.contains(niceItem)) continue;

        //New directory detected, add it to the menu
        auto *action = new QAction(niceItem, m_menu_addComparison);
        action->setCheckable(true);
        m_menu_addComparison->addAction(action);
    }
}

void GenericComparisonWidget::deleteResultTab(const QString &tabName) {
    auto tab = m_mapTabsByName.take(tabName);
    auto index = m_tabWidget->indexOf(tab);
    m_tabWidget->removeTab(index);
    tab->deleteLater();
}

void GenericComparisonWidget::slot_comparisonMenu_triggered(QAction *action) {
    //Add or Remove a result based on checkbox state
    //This uses action's text as tab name
    if (action && action->isChecked())
        addComparisonResult(action->text());
    else
        removeComparisonResult(action->text());
}

void GenericComparisonWidget::slot_updateSaveButton(int index) {
    auto widget = m_tabWidget->widget(index);
    auto tab = dynamic_cast<GenericGraphicsView *>(widget);
    updateSaveButton(tab);
}

void GenericComparisonWidget::updateSaveButton(GenericGraphicsView *tab) {
    if (tab != nullptr)
        m_pushButton_saveCurrentTab->setEnabled(!tab->isSaved());
}

void GenericComparisonWidget::on_pushButton_saveCurrentTab_clicked() {
    auto widget = m_tabWidget->currentWidget();
    auto tab = dynamic_cast<GenericGraphicsView *>(widget);
    if (tab) saveResult(tab);
}

void GenericComparisonWidget::updateResultFolderPath(const QString &newDirPath) {
    cleanup_comparisonMenu();
    configure_comparisonMenu(newDirPath);
}

void GenericComparisonWidget::cleanup_comparisonMenu() {
    //Cleanup, because results dir was changed
    //Remove opened tabs
    for (const auto &action : m_menu_addComparison->actions()) {
        if (action->isChecked()) {
            auto runName = action->text();
            removeComparisonResult(runName);
        }
    }
    //Clear menu entries
    m_menu_addComparison->clear();
}

void GenericComparisonWidget::changeEvent(QEvent *event) {
    if (event->type() == QEvent::LanguageChange) {
        // this event is sent if a translator is loaded
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
void GenericComparisonWidget::retranslateUi() {
    m_pushButton_addComparison->setText(tr("Compare ..."));
}

QTabWidget *GenericComparisonWidget::getTabWidget() const {
    return m_tabWidget;
}

const QMap<QString, QWidget *> &GenericComparisonWidget::getMapTabsByName() const {
    return m_mapTabsByName;
}
