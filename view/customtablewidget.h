#ifndef CUSTOMTABLEWIDGET_H
#define CUSTOMTABLEWIDGET_H


#include <QtGui>
#include <QStylePainter>
#include <QTableWidget>
#include <QAbstractButton>


class CustomTableWidget : public QTableWidget {
public:
    /**
     * Constructs a QTableWidget where the corner Button can be set and used
     * @param parent widget
     */
    explicit CustomTableWidget(QWidget *parent = nullptr);

    /**
     * Paints the given custom resources like label and icon on the button
     * @param o Given object
     * @param e Given event
     * @return status of the event
     */
    bool eventFilter(QObject *o, QEvent *e) override;
};

#endif //CUSTOMTABLEWIDGET_H
