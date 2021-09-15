#include "customlistwidget.h"

CustomListWidget::CustomListWidget(QWidget *parent) : QListWidget(parent) {
    connect(this, &CustomListWidget::currentItemChanged,
            this, &CustomListWidget::updateSelectionIcon);

    // Add full touch compliance
    this->setAttribute(Qt::WA_AcceptTouchEvents, true);
    this->setVerticalScrollMode(QAbstractItemView::ScrollPerPixel);
    this->setHorizontalScrollMode(QAbstractItemView::ScrollPerPixel);
    QScroller::grabGesture(this, QScroller::TouchGesture);
}

/*!
\reimp
*/
void CustomListWidget::addItem(const QString &label) {
    //QListWidget will delete all items when deleted,
    // so there is no need to free these items manually
    auto *item = new QListWidgetItem(this);
    item->setText(label);
    item->setIcon(QIcon(unselectedIconPath));
    QListWidget::addItem(item);
}

/*!
\reimp
*/
void CustomListWidget::addItems(const QStringList &labels) {
    for (const auto &item: labels) addItem(item);
}

void CustomListWidget::updateSelectionIcon(QListWidgetItem *current, QListWidgetItem *previous) {
    if (previous)
        previous->setIcon(QIcon(unselectedIconPath));
    if (current)
        current->setIcon(QIcon(selectedIconPath));
}
