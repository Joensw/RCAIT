#include "customtabwidget.h"
#include "customtabbar.h"

CustomTabWidget::CustomTabWidget(QWidget *parent)
{
    auto * tabbar = new CustomTabBar();
    this->setTabBar(tabbar);
}
