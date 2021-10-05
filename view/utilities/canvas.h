#ifndef CANVAS_H
#define CANVAS_H

#include <QGraphicsView>

/**
 * @brief Special graphics view which supports auto scaling of its contents.
 */
class Canvas : public QGraphicsView {
private:
    bool m_autoScale;

public:
    /**
     * @brief Constructs a Canvas
     * @param autoScale Controls whether the Canvas is auto-scaled. Defaults to true.
     */
    explicit Canvas(bool autoScale = true);

    /**
     * @brief Default destructor.
     */
    ~Canvas() override = default;

    /**
     * @brief Returns whether auto scale is enabled
     * @return state as a boolean
     */
    [[maybe_unused]] [[nodiscard]] bool getAutoScale() const;

    /**
     * @brief Enable or disable autoscaling
     * @param autoScale new auto scaling value
     */
    [[maybe_unused]] void setAutoScale(bool autoScale);

protected:

    /**
     * @brief Overridden method.
     * This is used for repainting with freshly calculated scaling factors.
     * @param paintEvent paint event that occurred.
     */
    void paintEvent(QPaintEvent *paintEvent) override;
};

#endif // CANVAS_H
