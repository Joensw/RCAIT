#include "popupmenu.h"
#include <QPushButton>

PopupMenu::PopupMenu(QPushButton *button, QWidget *parent)
        : QMenu(parent),
          m_pushButton_menu(button) {
}

void PopupMenu::showEvent(QShowEvent *event) {
    const auto &[x, y] = this->pos();
    QRect geo = m_pushButton_menu->geometry();
    this->move(x + geo.width() - geometry().width(), y);
}

void PopupMenu::mouseReleaseEvent(QMouseEvent *event) {
    auto *action = activeAction();
    if (action && action->isEnabled()) {
        action->setEnabled(false);
        QMenu::mouseReleaseEvent(event);
        action->setEnabled(true);
        action->trigger();
    } else
        QMenu::mouseReleaseEvent(event);
}
