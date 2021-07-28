#include "customtabbar.h"
#include <iostream>
#include <string>

CustomTabBar::CustomTabBar(QTabWidget *tabWidget) {
    m_tabWidget = tabWidget;
}

void CustomTabBar::paintEvent(QPaintEvent *e) {
    Q_UNUSED(e);
    int selected = m_tabWidget->currentIndex();
    QStylePainter painter(this);

    for (int i = 0; i < count(); ++i) {
        QStyleOptionTab option;
        initStyleOption(&option, i);
        QPixmap pixmap = option.icon.pixmap(option.iconSize);
        int height = option.rect.height();

        painter.drawControl(QStyle::CE_TabBarTabShape, option);
        // Draw the selected tab to get it "on top"
        auto offset = (i == selected) ? SELECTED_OFFSET(height) : OFFSET(height);
        option.rect.moveTop((int) offset);
        //Cut upper/lower parts of rectangle so the content is more centered
        option.rect.setHeight((int) (height - 2 * OFFSET(height)));
        painter.drawItemPixmap(option.rect, Qt::AlignTop | Qt::AlignHCenter, pixmap);
        painter.drawItemText(option.rect, Qt::AlignBottom | Qt::AlignHCenter, option.palette, true, option.text);
    }
}
