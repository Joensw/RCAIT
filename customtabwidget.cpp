#include "customtabwidget.h"
#include "customtabbar.h"

CustomTabWidget::CustomTabWidget(QWidget *parent)
{
    CustomTabBar * tabbar = new CustomTabBar();
    this->setTabBar(tabbar);
}
