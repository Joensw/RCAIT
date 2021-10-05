#ifndef GENERICCOMPARISONWIDGET_H
#define GENERICCOMPARISONWIDGET_H

#include <QWidget>
#include <QPushButton>
#include <QMenu>
#include <QDir>
#include <QTabWidget>
#include <QEvent>
#include <QStringBuilder>
#include <QTimer>
#include <type_traits>

#include <result.h>
#include <genericgraphicsview.h>
#include <popupmenu.h>
#include <savableresultswidget.h>

namespace Ui {
    class GenericComparisonWidget;
}

/**
 * @brief This class functions as a superclass for all specialised result widgets.
 * It includes code for displaying result tabs as well as comparing and saving functionality.
 */
class GenericComparisonWidget : public SavableResultsWidget {
Q_OBJECT

protected:
    /**
     * @brief   this event is called, when a new translator is loaded or the system language is changed
     */
    void changeEvent(QEvent *) override;

    /**
     * @attention This function truly deletes the tab. It will no longer occupy space.
     * @brief Deletes a given result.
     * @param tabName name of tab to be deleted.
     */
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
        tab->setName(tabName);
        m_tabWidget->addTab(tab, tabName);
        m_mapTabsByName[tabName] = tab;

        return tab;
    }

    /**
     * @brief Retranslate UI.
     * Subclasses can override this method to add own retranslation code.
     */
    virtual void retranslateUi();

    /**
     * @brief Get the tab widget which contains all result views.
     * @return tab widget pointer
     */
    [[maybe_unused]] [[nodiscard]] QTabWidget *getTabWidget() const;

    /**
     * @brief Get the Map which maps names to their corresponding tab .
     * @return Map which maps names to their corresponding tab.
     */
    [[maybe_unused]] [[nodiscard]] const QMap<QString, QWidget *> &getMapTabsByName() const;

    /**
     * @brief Sets up the basic GUI elements for the menu
     *
     */
    void configure_comparisonMenu();

public:
    /**
     * @brief Constructs a GenericComparisonWidget
     * @param parent parent widget (optional)
     */
    explicit GenericComparisonWidget(QWidget *parent = nullptr);

    /**
     * @brief Destructor of this class.
     */
    ~GenericComparisonWidget() override;

    /**
     * @brief Updates the folder path to check for results to compare.
     * @param newDirPath path to new directory
     */
    virtual void updateResultFolderPath(const QString &newDirPath);

    /**
     * @brief Update the saved state of a result view tab
     * @param tab tab that changed its state
     */
    void updateSaveState(GenericGraphicsView *tab) override;

private:
    static constexpr auto PREFIX_TAB_SAVED = "\uF79A ";
    static constexpr auto COMPARISON_BUTTON_ICON = ":/UISymbols/UI_Add_Result_Comparison_Icon.svg";
    static constexpr auto FONT_NAME = "Inter Monospace";
    static constexpr auto FONT_SIZE = 9;
    static constexpr auto COMPARE_BUTTON_LABEL = QT_TR_NOOP("Compare ...");

    Ui::GenericComparisonWidget *ui;
    QTabWidget *m_tabWidget;
    QString m_resultsDir;
    QMap<QString, QWidget *> m_mapTabsByName;
    QScopedPointer<QPushButton> m_pushButton_addComparison;
    QScopedPointer<QMenu> m_menu_addComparison;
    QPushButton *m_pushButton_saveCurrentTab;

    void configure_comparisonButton();

    void cleanup_oldResults();

    virtual void addComparisonResult(const QString &runNameToCompare) = 0;

    virtual void removeComparisonResult(const QString &runNameToCompare) = 0;

    void saveResult(GenericGraphicsView *view) override = 0;

private slots:

    void slot_comparisonMenu_triggered(QAction *action);

    void slot_updateSaveButton(int index) override;

    void on_pushButton_saveCurrentTab_clicked();

};

#endif // GENERICCOMPARISONWIDGET_H
