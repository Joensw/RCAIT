#ifndef CLASSIFICATIONRESULTSWIDGET_H
#define CLASSIFICATIONRESULTSWIDGET_H

#include <QWidget>
#include <QPushButton>
#include <QMenu>
#include <classificationresult.h>
#include "classificationresultview.h"
#include "genericcomparisonwidget.h"

/**
 * @brief The ClassificationResultsWidget is used for displaying and comparing classification results.
 */
class ClassificationResultsWidget : public GenericComparisonWidget {
Q_OBJECT

public:
    /**
     * @brief Constructs a classification result widget
     * @param parent QWidget parent object (optional)
     */
    explicit ClassificationResultsWidget(QWidget *parent = nullptr);

    /**
     * @brief Default destructor
     */
    ~ClassificationResultsWidget() override = default;

    /**
     * @brief Add a new classification result to display
     * @param result result to be added
     */
    void addClassificationResult(ClassificationResult *result);

private:
    static constexpr auto PLACEHOLDER_TAB_INDEX = 0;
    static constexpr auto PLACEHOLDER_TAB_ICON = ":/TabIcons/Filled/Results_Accuracy_Tab_Icon.svg";

    QMap<GenericGraphicsView *, ClassificationResult *> m_mapResultsByTab;

    void addComparisonResult(const QString &runNameToCompare) override;

    void removeComparisonResult(const QString &runNameToCompare) override;

    void saveResult(GenericGraphicsView *view) override;

    void configure_placeholderTab();

signals:

    /**
     * @brief Signal is emitted when a result tab was created (for comparison) and data is requested.
     * @param view tab to be filled with data
     * @param runNameToCompare name of the result
     */
    void sig_comparison_loadClassificationResultData(ClassificationResultView *view, const QString &runNameToCompare);

    /**
     * @brief Signal is emitted when a result tab was created (for comparison) and graphics are requested.
     * @param view tab that will display the graphics
     * @param runNameToCompare name of the result
     */
    void
    sig_comparison_loadClassificationResultGraphics(ClassificationResultView *view, const QString &runNameToCompare);

    /**
     * @brief Signal is emitted when a result tab was created (after a classification) and data is requested.
     * @param view tab to be filled with data
     * @param result contains the relevant data for parsing
     */
    void sig_normal_loadClassificationResultData(ClassificationResultView *view, ClassificationResult *result);

    /**
     * @brief Signal is emitted when a result tab was created (after a classification) and graphics are requested.
     * @param receiver tab that will display the graphics
     * @param result result that contains the relevant data
     */
    void sig_normal_generateClassificationResultGraphics(GenericGraphicsView *receiver, ClassificationResult *result);

    /**
     * @brief Signal is emitted when the save button was clicked.
     * @param result result to be saved
     * @param success bool to report success state back to the view component
     */
    void sig_save_ClassificationResult(ClassificationResult *result, bool &success);

};

#endif // CLASSIFICATIONRESULTSWIDGET_H
