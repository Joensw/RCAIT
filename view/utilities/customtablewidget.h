#ifndef CUSTOMTABLEWIDGET_H
#define CUSTOMTABLEWIDGET_H

#include <QtGui>
#include <QStylePainter>
#include <QTableWidget>
#include <QAbstractButton>
#include <QScroller>

/**
 * @brief This class allows adding pre-filled data rows as well as
 * adding a functional button in the corner of the table (hacky)
 */
class CustomTableWidget : public QTableWidget {
public:
    /**
     * @brief Constructs a QTableWidget where the corner Button can be set and used
     * @param parent widget
     */
    explicit CustomTableWidget(QWidget *parent = nullptr);

    /**
     * @brief Tries to find the 'hidden' corner button from Qt's original implementation
     * @return pointer to button or nullptr otherwise
     */
    QAbstractButton *getCornerButton();

    /**
     * @brief Add a row to the table
     * @param identifier row name
     * @param data row data
     * @return row number
     */
    int addTableRow(const QString &identifier, const QStringList &data);

    /**
     * @brief Remove row from table
     * @param identifier row name
     * @return success status
     */
    bool removeTableRow(const QString &identifier);

    /**
     * @brief Access a particular cell of the table
     * @param row row number
     * @param column column number
     * @return item at the particular position
     */
    QTableWidgetItem *operator()(int row, int column) const;

    /**
     * @brief Access a particular cell of the table. Same as () operator.
     * @param row row number
     * @param column column number
     * @return item at the particular position
     */
    [[nodiscard]] QTableWidgetItem *at(int row, int column) const;

private:

    QMap<QString, QStringList> m_data;

    /**
     * Paints the given custom resources like label and icon on the button
     * @param o Given object
     * @param e Given event
     * @return status of the event
     */
    bool eventFilter(QObject *o, QEvent *e) override;

};

#endif //CUSTOMTABLEWIDGET_H
