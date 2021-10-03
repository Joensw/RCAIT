#include "customtabwidget.h"

CustomTabWidget::CustomTabWidget(QWidget *parent)
{
    Q_UNUSED(parent)
    auto * tabbar = new CustomTabBar(this);
    this->setTabBar(tabbar);
}
