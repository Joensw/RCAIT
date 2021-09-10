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

#define OFFSET(x) ((int) x*0.12)
#define SELECTED_OFFSET(x) ((int) x*0.08)

/**
 * @brief The CustomTabBar class is used in the CustomTabWidget
 */
class CustomTabBar : public QTabBar {
Q_OBJECT
public:
    /**
     * @brief CustomTabBar constructor
     * @param tabWidget Associated TabWidget
     */
    CustomTabBar(QTabWidget *tabWidget);

protected:
    /**
     * @brief Overridden function to paint the widget
     */
    void paintEvent(QPaintEvent *) override;

private:
    QTabWidget *m_tabWidget;
};

#endif // CUSTOMTABBAR_H
