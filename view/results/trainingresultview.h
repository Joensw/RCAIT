#ifndef TRAININGRESULTVIEW_H
#define TRAININGRESULTVIEW_H

#include <QWidget>
#include <QGraphicsItem>
#include <QGraphicsScene>
#include "abstractgraphicsview.h"

namespace Ui {
    class TrainingResultView;
}

class TrainingResultView : public AbstractGraphicsView, public QWidget {

protected:
    // this event is called, when a new translator is loaded or the system language is changed
    void changeEvent(QEvent *) override;

public:
    explicit TrainingResultView(QWidget *parent = nullptr);

    ~TrainingResultView();

    void setLossCurve(QGraphicsItem *lossCurveImage) override;

    void setConfusionMatrix(QGraphicsItem *matrixImage) override;

    void setMostMisclassifiedImages(QList<QImage> images);

private:
    Ui::TrainingResultView *ui;
};

#endif // TRAININGRESULTVIEW_H
