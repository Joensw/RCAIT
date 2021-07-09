#include "customlistwidget.h"

static const QString selectedIconPath = ":/Resources/UISymbols/ListItem_Selected.svg";
static const QString unselectedIconPath = ":/Resources/UISymbols/ListItem_Unselected.svg";
static const QIcon selectedIcon = QIcon(selectedIconPath);
static const QIcon unselectedIcon = QIcon(unselectedIconPath);

CustomListWidget::CustomListWidget(QWidget *parent) : QListWidget(parent) {
    connect(this, &CustomListWidget::currentItemChanged, this, &CustomListWidget::updateSelectionIcon);

}

void CustomListWidget::addItem(const QString &label) {
    auto *item = new QListWidgetItem(this);
    item->setText(label);
    item->setIcon(unselectedIcon);
    QListWidget::addItem(item);
}

void CustomListWidget::addItems(const QStringList &labels) {
    for (const auto &item : labels){
        addItem(item);
    }
}

void CustomListWidget::updateSelectionIcon(QListWidgetItem *current, QListWidgetItem *previous) {
    if (previous){
        previous->setIcon(unselectedIcon);
    }
    if (current) {
        current->setIcon(selectedIcon);
    }
}
