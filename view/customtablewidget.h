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
     * Tries to find the 'hidden' corner button from Qt's original implementation
     * @return pointer to button or nullptr otherwise
     */
    QAbstractButton *getCornerButton();

    int addTableRow(const QString &identifier, const QStringList &data);

    bool removeTableRow(const QString &identifier);

    QTableWidgetItem * operator()(int row, int column) const;

    [[nodiscard]] QTableWidgetItem *at(int row, int column) const;

private:

    QMap<QString,QStringList> m_data;

    /**
     * Paints the given custom resources like label and icon on the button
     * @param o Given object
     * @param e Given event
     * @return status of the event
     */
    bool eventFilter(QObject *o, QEvent *e) override;

};

#endif //CUSTOMTABLEWIDGET_H
