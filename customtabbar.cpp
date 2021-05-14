#include "customtabbar.h"
#include <iostream>
#include <string>

CustomTabBar::CustomTabBar(){
}

    void CustomTabBar::paintEvent(QPaintEvent * e) {
        Q_UNUSED(e);
//        QTabBar::paintEvent(e);
        QStylePainter painter(this);
        for(int i = 0; i < count(); ++i) {
            QStyleOptionTab option;
            initStyleOption(&option, i);
            painter.drawControl(QStyle::CE_TabBarTabShape, option);
            QPixmap pixmap = option.icon.pixmap(option.iconSize);
            int height = option.rect.height();
            option.rect.setHeight(50);
            painter.drawItemPixmap(option.rect, Qt::AlignVertical_Mask|Qt::AlignHCenter, pixmap);
            option.rect.setHeight(height);
            QString text = option.text.replace("%n","\n");
            painter.drawItemText(option.rect, Qt::AlignVCenter|Qt::AlignHCenter, palette(), 1, "\n\n\n"+text);
        }

    }
