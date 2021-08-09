#include "popupmenu.h"
#include <QPushButton>

PopupMenu::PopupMenu(QPushButton *button, QWidget *parent)
        : QMenu(parent), m_pushButton_menu(button) {
}

void PopupMenu::showEvent(QShowEvent *event) {
    QPoint p = this->pos();
    QRect geo = m_pushButton_menu->geometry();
    this->move(p.x() + geo.width() - this->geometry().width(), p.y());
}