#ifndef TOPACCURACIESVIEW_H
#define TOPACCURACIESVIEW_H

#include <QWidget>
#include <QMap>
#include <QTableWidgetItem>
#include <QPushButton>
#include "genericgraphicsview.h"

namespace Ui {
    class TopAccuraciesView;
}

/**
 * @brief This class is a view wrapper for top accuracies values
 * of training results.
 */
class TopAccuraciesView : public GenericGraphicsView {
Q_OBJECT

protected:
    /**
     * @brief this event is called, when a new translator is loaded or the system language is changed
     */
    void changeEvent(QEvent *) override;

public:
    /**
     * @brief Constructs a TopAccuraciesView
     * @param tabWidget TabWidget parent which will hold this object
     * @param parent QWidget parent (optional)
     */
    explicit TopAccuraciesView(SavableResultsWidget *tabWidget, QWidget *parent = nullptr);

    /**
     * @brief Adds a new entry of top accuracies data
     * @param identifier name of the corresponding training result
     * @param top1 top1 accuracy value
     * @param top5 top5 accuracy value
     */
    void addTopAccuraciesEntry(const QString &identifier, double top1, double top5);

    /**
     * @brief Remove an entry of top accuracies data by identifier
     * @param identifier name of the corresponding training result to be removed
     */
    void removeTopAccuraciesEntry(const QString &identifier);

    /**
     * @brief Set the top accuracies graphics to be displayed
     * @param topAccuraciesImage image to be displayed, passed via QSharedPointer
     */
    void setTopAccuraciesGraphics(const QSharedPointer<QGraphicsItem> &topAccuraciesImage) override;

    /**
     * @brief Change the 'Update Graphics' button state
     * @param enabled new state to be set to
     */
    [[maybe_unused]] void setUpdateGraphicsButtonState(bool enabled);

    /**
     * @brief Get the state of the 'Update Graphics' button
     * @return button state
     */
    [[maybe_unused]] [[nodiscard]] bool getUpdateGraphicsButtonState();

    /**
     * @brief Get the current top accuracies graphics image
     * @return QSharedPointer pointing to the graphics
     */
    [[maybe_unused]] [[nodiscard]] const QSharedPointer<QGraphicsItem> &getTopAccuraciesImage() const;

    /**
     * @brief Destructor for this class.
     */
    ~TopAccuraciesView() override;

signals:

    /**
     * @brief Signal is emitted when the 'Update graphics' button is clicked.
     * @param receiver receiver to get the graphics
     */
    void sig_normal_requestTopAccuraciesGraphics(TopAccuraciesView *receiver);

private slots:

    void slot_pushButton_updateGraphics_clicked();

private:
    static constexpr auto FONT_NAME = "Inter Monospace";
    static constexpr auto FONT_SIZE = 8;

    static constexpr auto NUMBER_FORMAT = 'f';
    static constexpr auto NUMBER_PRECISION = 2;

    static constexpr auto TABLE_COLUMN_COUNT = 2;
    static constexpr auto TOP1_HEADER = QT_TR_NOOP("Top 1%");
    static constexpr auto TOP5_HEADER = QT_TR_NOOP("Top 5%");
    static constexpr auto TOP1_COLOR = QColorConstants::Svg::royalblue;
    static constexpr auto TOP5_COLOR = QColorConstants::Svg::orange;

    static constexpr auto GRAPHICS_SCALING_FACTOR = 0.9;
    static constexpr auto UPDATE_GRAPHICS_BUTTON_ICON = ":/UISymbols/UI_Reload_Icon.svg";
    static constexpr auto UPDATE_GRAPHICS_BUTTON_TOOLTIP = QT_TR_NOOP("Update graphics...");

    Ui::TopAccuraciesView *ui;
    QAbstractButton *m_pushButton_updateGraphics{};

    QSharedPointer<QGraphicsItem> m_topAccuraciesImage;
    QScopedPointer<QGraphicsScene> m_topAccuraciesScene;

    void configure_updateGraphicsButton();

    void retranslateUi();
};

#endif // TOPACCURACIESVIEW_H
