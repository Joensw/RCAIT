#ifndef GENERICGRAPHICSVIEW_H
#define GENERICGRAPHICSVIEW_H

#include <QGraphicsItem>
#include <QWidget>

class GenericGraphicsView : public QWidget {
Q_OBJECT

public:
    explicit GenericGraphicsView(QWidget *parent = nullptr) : QWidget(parent) {}

    virtual void setAccuracyCurve(const QSharedPointer<QGraphicsItem> &accuracyCurveImage) {};

    virtual void setConfusionMatrix(const QSharedPointer<QGraphicsItem> &matrixImage) {};

    virtual void setTopAccuraciesGraphics(const QSharedPointer<QGraphicsItem> &topAccuraciesImage) {};

    virtual void setClassificationGraphics(const QSharedPointer<QGraphicsItem> &classificationGraphicsImage) {};

    [[nodiscard]] bool isSaved() const { return m_isSaved; };

    void setSaved(bool isSaved) { m_isSaved = isSaved; };

private:
    bool m_isSaved = false;
};

#endif // GENERICGRAPHICSVIEW_H
