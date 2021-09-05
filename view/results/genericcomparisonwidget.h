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
#include "genericgraphicsview.h"
#include "popupmenu.h"
#include "savableresultswidget.h"

namespace Ui {
    class GenericComparisonWidget;
}

class GenericComparisonWidget : public SavableResultsWidget {
Q_OBJECT

protected:
    // this event is called, when a new translator is loaded or the system language is changed
    void changeEvent(QEvent *) override;

    void deleteResultTab(const QString &tabName);

    /**
     * @brief Create a new result tab and add it to the tabWidget
     * @attention C++ templates have to be defined in the header.
     * There is no other way.
     * Ugly, but that's the recommended way to do it.
     * @tparam T extends GenericGraphicsView, tab type to be created
     * @param tabName name of the tab to be created
     * @return created tab of type T
     */
    template<typename T, typename = std::enable_if<std::is_base_of_v<GenericGraphicsView, T>>>
    T *createResultTab(const QString &tabName) {
        auto *tab = new T(this);
        m_tabWidget->addTab(tab, tabName);
        m_mapTabsByName[tabName] = tab;

        return tab;
    }

    virtual void retranslateUi();

    [[maybe_unused]] [[nodiscard]] QTabWidget *getTabWidget() const;

    [[maybe_unused]] [[nodiscard]] const QMap<QString, QWidget *> &getMapTabsByName() const;

public:
    explicit GenericComparisonWidget(QWidget *parent = nullptr);

    ~GenericComparisonWidget() override;

    virtual void updateResultFolderPath(const QString &newDirPath);

    void updateSaveButton(GenericGraphicsView *tab) override;

private:
    Ui::GenericComparisonWidget *ui;
    QTabWidget *m_tabWidget;
    QMap<QString, QWidget *> m_mapTabsByName;
    QScopedPointer<QPushButton> m_pushButton_addComparison;
    QScopedPointer<QMenu> m_menu_addComparison;
    QPushButton *m_pushButton_saveCurrentTab;

    void configure_comparisonButton();

    void configure_comparisonMenu(const QString &targetDir);

    void cleanup_comparisonMenu();

    virtual void addComparisonResult(const QString &runNameToCompare) = 0;

    virtual void removeComparisonResult(const QString &runNameToCompare) = 0;

    void saveResult(GenericGraphicsView *view) override = 0;

private slots:

    void slot_comparisonMenu_triggered(QAction *action);

    void slot_updateSaveButton(int index) override;

    void on_pushButton_saveCurrentTab_clicked() override;

};

#endif // GENERICCOMPARISONWIDGET_H
