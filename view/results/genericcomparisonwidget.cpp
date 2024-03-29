#include "genericcomparisonwidget.h"
#include "ui_genericcomparisonwidget.h"


GenericComparisonWidget::GenericComparisonWidget(QWidget *parent)
        : SavableResultsWidget(parent),
          ui(new Ui::GenericComparisonWidget),
          m_pushButton_addComparison(new QPushButton(this)),
          m_menu_addComparison(new PopupMenu(&*m_pushButton_addComparison)) {

    ui->setupUi(this);

    //Setup variables
    m_tabWidget = ui->tabWidget_compareResults;
    m_pushButton_saveCurrentTab = ui->pushButton_saveCurrentTab;



    //Connect internal signals and slots
    connect(&*m_menu_addComparison, &QMenu::triggered, this,
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
    const auto icon = QIcon(COMPARISON_BUTTON_ICON);
    m_pushButton_addComparison->setIcon(icon);
    m_pushButton_addComparison->setFlat(true);
    m_pushButton_addComparison->setMenu(&*m_menu_addComparison);

    m_tabWidget->setCornerWidget(&*m_pushButton_addComparison, Qt::TopRightCorner);
}

void GenericComparisonWidget::configure_comparisonMenu() const {

    QFont inter(FONT_NAME, FONT_SIZE);
    m_menu_addComparison->setFont(inter);

    QStringList oldMenuEntries;
    for (const auto &item: m_menu_addComparison->actions()) {
        oldMenuEntries << item->text();
    }
    //Add new compare button menu entries
    auto dir = QDir(m_resultsDir);
    auto entryList = dir.entryList(QDir::AllDirs | QDir::NoDotAndDotDot);

    for (const auto &resultEntry: entryList) {
        //Leave already contained entries in the menu
        auto niceEntry = Result::niceRepresentation(resultEntry);
        if (oldMenuEntries.contains(niceEntry)) continue;

        //New result detected, add it to the menu
        auto *action = new QAction(niceEntry, &*m_menu_addComparison);
        action->setCheckable(true);
        action->setChecked(m_mapTabsByName.contains(niceEntry));
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
    if (!action) return;

    //Keep user from click-spamming
    m_menu_addComparison->setEnabled(false);
    QTimer::singleShot(500, this, [this] { m_menu_addComparison->setEnabled(true); });
    //Add or Remove a result based on checkbox state
    //This uses action's text as tab name
    if (action->isChecked())
        addComparisonResult(action->text());
    else
        removeComparisonResult(action->text());
}

void GenericComparisonWidget::slot_updateSaveButton(int index) {
    auto widget = m_tabWidget->widget(index);
    auto tab = dynamic_cast<GenericGraphicsView *>(widget);
    updateSaveState(tab);
}

void GenericComparisonWidget::updateSaveState(GenericGraphicsView *tab) {
    if (!tab) return;
    bool canBeSaved = !tab->isSaved();
    auto index = m_tabWidget->indexOf(tab);
    auto tabName = canBeSaved ? PREFIX_TAB_SAVED % tab->getName()
                              : tab->getName();

    m_tabWidget->setTabText(index, tabName);

    //Check if we are still on the tab to be updated. Otherwise, do nothing.
    if (index == m_tabWidget->currentIndex())
        m_pushButton_saveCurrentTab->setEnabled(canBeSaved);
}

[[maybe_unused]] void GenericComparisonWidget::on_pushButton_saveCurrentTab_clicked() {
    auto widget = m_tabWidget->currentWidget();
    auto tab = dynamic_cast<GenericGraphicsView *>(widget);
    if (tab) saveResult(tab);
}

void GenericComparisonWidget::updateResultFolderPath(const QString &newDirPath) {
    m_resultsDir = newDirPath;
    cleanup_oldResults();
    configure_comparisonMenu();
}

void GenericComparisonWidget::cleanup_oldResults() {
    //Cleanup, because results dir was changed
    //Remove opened tabs
    for (const auto &action: m_menu_addComparison->actions()) {
        if (action->isChecked()) {
            auto runName = action->text();
            removeComparisonResult(runName);
        }
    }
    //Clear menu entries
    m_menu_addComparison->clear();
}

[[maybe_unused]] QTabWidget *GenericComparisonWidget::getTabWidget() const {
    return m_tabWidget;
}

[[maybe_unused]] const QMap<QString, QWidget *> &GenericComparisonWidget::getMapTabsByName() const {
    return m_mapTabsByName;
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
    m_pushButton_addComparison->setText(tr(COMPARE_BUTTON_LABEL));
}
