#ifndef GENERICCOMPARISONWIDGET_H
#define GENERICCOMPARISONWIDGET_H


#include <QWidget>
#include <QPushButton>
#include <QMenu>
#include <QDir>
#include <QTabWidget>
#include <QEvent>
#include <type_traits>
#include "result.h"
#include "abstractgraphicsview.h"
#include "popupmenu.h"

using namespace std;

namespace Ui {
    class GenericComparisonWidget;
}

class GenericComparisonWidget : public QWidget {
Q_OBJECT

protected:
    QTabWidget *m_tabWidget;
    QMap<QString, QWidget *> m_mapTabsByName;

    // this event is called, when a new translator is loaded or the system language is changed
    void changeEvent(QEvent *) override;

    void deleteResultTab(const QString &tabName);

    /**
     * @brief C++ templates have to be defined in the header.
     * There is no other way.
     * Ugly, but that's the recommended way to do it.
     * @tparam T extends AbstractGraphicsView, tab type to be created
     * @param tabName name of the tab to be created
     * @return created tab of type T
     */
    template<typename T, typename = std::enable_if<std::is_base_of_v<AbstractGraphicsView, T>>>
            T *createResultTab(const QString &tabName){
                auto *tab = new T(this);
                m_tabWidget->addTab(tab, tabName);
                m_mapTabsByName[tabName] = tab;

                return tab;
            };


    virtual void retranslateUi();

public:
    explicit GenericComparisonWidget(QWidget *parent = nullptr);

    ~GenericComparisonWidget();

    void updateResultFolderPath(const QString &newDirPath);

private:
    Ui::GenericComparisonWidget *ui;
    QPushButton *m_pushButton_addComparison = new QPushButton(this);
    QPushButton *m_pushButton_saveCurrentTab;
    QMenu *m_menu_addComparison = new PopupMenu(m_pushButton_addComparison);

    void configure_comparisonButton();

    void configure_comparisonMenu(const QString &targetDir);

    void cleanup_comparisonMenu();

    virtual void addComparisonResult(const QString &runNameToCompare) = 0;

    virtual void removeComparisonResult(const QString &runNameToCompare) = 0;

private slots:

    void slot_comparisonMenu_triggered(QAction *action);

    void slot_updateSaveButton(int index);
};

#endif // GENERICCOMPARISONWIDGET_H
