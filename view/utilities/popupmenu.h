#ifndef POPUPMENU_H
#define POPUPMENU_H

#include <QMenu>
#include <QPushButton>
#include <QWidget>

/**
 * @brief Special menu used together with QPushButton's menu() function
 */
class PopupMenu : public QMenu {
Q_OBJECT
protected:
    /**
     * @attention In the default implementation of QMenu, after checking/unchecking an entry, the menu will close.
     * This is likely a bug and not documented.
     * This function is a workaround for that behaviour.
     * @brief Used to prevent menu from closing when checking/unchecking an entry.
     * @param event mouse event
     */
    void mouseReleaseEvent(QMouseEvent *event) override;

public:
    /**
     * Creates a new popup menu
     * @param button associated push button used to open this menu
     * @param parent (optional) parent widget
     */
    explicit PopupMenu(QPushButton *button, QWidget *parent = nullptr);

    /**
     * Show the popup menu respecting the buttons position
     * @param event show event
     */
    void showEvent(QShowEvent *event) override;

private:
    QPushButton *m_pushButton_menu;
};

#endif // POPUPMENU_H
