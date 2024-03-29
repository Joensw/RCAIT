#ifndef CUSTOMLISTWIDGET_H
#define CUSTOMLISTWIDGET_H

#include <QObject>
#include <QWidget>
#include <QListWidget>
#include <QScroller>

/**
 * It is used in the UI for example for the project list and model list.
 * The elements of the list widget have specialized depictions to represent when and element has been selected / unselected.
 * @brief The CustomListWidget class is a specialized implementation of a QListWidget.
 */
class CustomListWidget : public QListWidget {
Q_OBJECT

private:
    static constexpr auto selectedIconPath = ":/UISymbols/ListItem_Selected.svg";
    static constexpr auto unselectedIconPath = ":/UISymbols/ListItem_Unselected.svg";
public:
    /**
     * @brief CustomListWidget create a new CustomListWidget
     * @param parent optional parent arguemnt
     */
    explicit CustomListWidget(QWidget *parent = nullptr);

    /**
     * @brief addItem add a new element to the lest
     * @param label name of the element
     */
    void addItem(const QString &label);

    /**
     * @brief addItems add a list of elements to the list
     * @param labels list of names of the elements
     */
    void addItems(const QStringList &labels);

private slots:

    static void updateSelectionIcon(QListWidgetItem *current, QListWidgetItem *previous);
};

#endif // CUSTOMLISTWIDGET_H
