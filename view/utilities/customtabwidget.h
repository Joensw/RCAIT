#ifndef CUSTOMTABWIDGET_H
#define CUSTOMTABWIDGET_H

#include <QTabWidget>
#include <QWidget>
#include <customtabbar.h>

/**
 * @brief The CustomTabWidget class is used to switch between different widgets layered on top of each other
 */
class CustomTabWidget : public QTabWidget {
public:
    /**
     * @brief CustomTabWidget creates a customTabWidget
     * @param parent optional parent argument
     */
    explicit CustomTabWidget(QWidget *parent = nullptr) {
        Q_UNUSED(parent)
        setTabBar(new CustomTabBar(this));
    };
};

#endif // CUSTOMTABWIDGET_H
