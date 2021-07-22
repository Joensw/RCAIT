#ifndef CUSTOMTABBAR_H
#define CUSTOMTABBAR_H
#include <QtCore/QVariant>
#include <QtWidgets/QApplication>
#include <QtWidgets/QGraphicsView>
#include <QtWidgets/QGridLayout>
#include <QtWidgets/QMainWindow>
#include <QtWidgets/QPushButton>
#include <QtWidgets/QSplitter>
#include <QtWidgets/QStatusBar>
#include <QtWidgets/QTabWidget>
#include <QtWidgets/QWidget>
#include <QtWidgets/QStylePainter>
#include <QtWidgets/QTabBar>
#include <QStyleOptionTab>

/**
 * @brief The CustomTabBar class is used in the CustomTabWidget
 */
class CustomTabBar : public QTabBar
{
public:
    /**
     * @brief CustomTabBar create a new CustomTabBar
     */
    CustomTabBar();
protected:
    void paintEvent(QPaintEvent *);
};

#endif // CUSTOMTABBAR_H
