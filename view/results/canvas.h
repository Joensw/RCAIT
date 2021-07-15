#ifndef CANVAS_H
#define CANVAS_H

#include <QGraphicsView>

class Canvas : public QGraphicsView {
private:
    bool m_autoScale;

public:
    Canvas(bool autoScale = true);

    virtual ~Canvas() = default;

    [[nodiscard]] bool autoScale() const;

    void setAutoScale(bool autoScale);

protected:

    virtual void paintEvent(QPaintEvent *pQEvent) override;
};

#endif // CANVAS_H
