#ifndef CANVAS_H
#define CANVAS_H

#include <QGraphicsView>

class Canvas : public QGraphicsView {
private:
    bool m_autoScale;

public:
    explicit Canvas(bool autoScale = true);

    ~Canvas() override = default;

    [[maybe_unused]] [[nodiscard]] bool getAutoScale() const;

    [[maybe_unused]] void setAutoScale(bool autoScale);

protected:

    void paintEvent(QPaintEvent *pQEvent) override;
};

#endif // CANVAS_H