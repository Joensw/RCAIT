#include "customtablewidget.h"

CustomTableWidget::CustomTableWidget(QWidget *parent) : QTableWidget(parent) {
    auto *cornerButton = getCornerButton();
    if (cornerButton)
        cornerButton->installEventFilter(this);
}

QAbstractButton *CustomTableWidget::getCornerButton(){
    return findChild<QAbstractButton *>();
}

bool CustomTableWidget::eventFilter(QObject *o, QEvent *e) {
    if (e->type() != QEvent::Paint) return QTableWidget::eventFilter(o, e);
    auto *button = qobject_cast<QAbstractButton *>(o);
    if (!button) return false;
    QStyleOptionHeader opt;
    opt.initFrom(button);
    QStyle::State state = QStyle::State_None;
    if (button->isEnabled())
        state |= QStyle::State_Enabled;
    if (button->isActiveWindow())
        state |= QStyle::State_Active;
    if (button->isDown())
        state |= QStyle::State_Sunken;
    opt.state = state;
    opt.rect = button->rect();
    //Painting icon and text, only difference to Qt's implementation
    opt.icon = button->icon();
    opt.iconAlignment = Qt::AlignHCenter | Qt::AlignVCenter;
    opt.text = button->text();
    opt.position = QStyleOptionHeader::OnlyOneSection;
    QStylePainter painter(button);
    painter.drawControl(QStyle::CE_Header, opt);
    //Finish event
    return true;
}
