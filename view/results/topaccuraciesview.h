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

class TopAccuraciesView : public GenericGraphicsView {
Q_OBJECT

protected:
    // this event is called, when a new translator is loaded or the system language is changed
    void changeEvent(QEvent *) override;

public:
    explicit TopAccuraciesView(SavableResultsWidget *tabWidget, QWidget *parent = nullptr);

    void addTopAccuraciesEntry(const QString &identifier, double top1, double top5);

    void removeTopAccuraciesEntry(const QString &identifier);

    void setTopAccuraciesGraphics(const QSharedPointer<QGraphicsItem> &topAccuraciesImage) override;

    [[maybe_unused]] void updateGraphicsButton_setEnabled(bool enabled);

    [[maybe_unused]] [[nodiscard]] bool updateGraphicsButton_isEnabled();

    [[maybe_unused]] [[nodiscard]] const QSharedPointer<QGraphicsItem> &getTopAccuraciesImage() const;

    ~TopAccuraciesView() override;

signals:

    void sig_normal_requestTopAccuraciesGraphics(TopAccuraciesView *receiver);

private slots:

    void slot_pushButton_updateGraphics_clicked();

private:
    static constexpr auto FONT_NAME = "Inter Monospace";
    static constexpr auto FONT_SIZE = 8;

    static constexpr auto NUMBER_FORMAT = 'f';
    static constexpr auto NUMBER_PRECISION = 2;

    static constexpr auto TABLE_COLUMN_COUNT = 2;
    static constexpr auto TOP1_HEADER = "Top 1%";
    static constexpr auto TOP5_HEADER = "Top 5%";
    static constexpr auto TOP1_COLOR = "royal blue";
    static constexpr auto TOP5_COLOR = "orange";

    static constexpr auto GRAPHICS_SCALING_FACTOR = 0.9;
    static constexpr auto UPDATE_GRAPHICS_BUTTON_ICON = ":/UISymbols/UI_Reload_Icon.svg";
    static constexpr auto UPDATE_GRAPHICS_BUTTON_TOOLTIP = "Update graphics...";

    Ui::TopAccuraciesView *ui;
    QAbstractButton *m_pushButton_updateGraphics{};

    QSharedPointer<QGraphicsItem> m_topAccuraciesImage;

    void configure_updateGraphicsButton();

    void retranslateUi();
};

#endif // TOPACCURACIESVIEW_H
