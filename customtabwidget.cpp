#include "customtabwidget.h"
#include "customtabbar.h"

CustomTabWidget::CustomTabWidget(QWidget *parent)
{
    Q_UNUSED(parent)
    auto * tabbar = new CustomTabBar();
    this->setTabBar(tabbar);
}
