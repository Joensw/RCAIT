#ifndef CANVAS_H
#define CANVAS_H

class Canvas : public QGraphicsView {
private:
    bool mAutoScale;

public:
    Canvas(bool autoScale = true);

    virtual ~Canvas() = default;

    bool autoScale() const { return mAutoScale; }

    void setAutoScale(bool autoScale);

protected:

    virtual void paintEvent(QPaintEvent *pQEvent) override;
};

#endif // CANVAS_H
