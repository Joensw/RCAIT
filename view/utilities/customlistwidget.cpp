#include "customlistwidget.h"

//Definitions
const QString selectedIconPath = ":/UISymbols/ListItem_Selected.svg";
const QString unselectedIconPath = ":/UISymbols/ListItem_Unselected.svg";

CustomListWidget::CustomListWidget(QWidget *parent) : QListWidget(parent) {
    connect(this, &CustomListWidget::currentItemChanged, this, &CustomListWidget::updateSelectionIcon);

    // Add full touch compliance
    this->setAttribute(Qt::WA_AcceptTouchEvents,true);
    this->setVerticalScrollMode(QAbstractItemView::ScrollPerPixel);
    this->setHorizontalScrollMode(QAbstractItemView::ScrollPerPixel);
    QScroller::grabGesture(this,QScroller::TouchGesture);
}

void CustomListWidget::addItem(const QString &label) {
    auto *item = new QListWidgetItem(this);
    item->setText(label);
    item->setIcon(QIcon(unselectedIconPath));
    QListWidget::addItem(item);
}

void CustomListWidget::addItems(const QStringList &labels) {
    for (const auto &item : labels){
        addItem(item);
    }
}

void CustomListWidget::updateSelectionIcon(QListWidgetItem *current, QListWidgetItem *previous) {
    if (previous){
        previous->setIcon(QIcon(unselectedIconPath));
    }
    if (current) {
        current->setIcon(QIcon(selectedIconPath));
    }
}
