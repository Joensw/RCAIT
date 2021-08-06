#ifndef POPUPMENU_H
#define POPUPMENU_H

#include <QMenu>
#include <QPushButton>
#include <QWidget>

class PopupMenu : public QMenu {
Q_OBJECT
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
