#ifndef TRAININGRESULTVIEW_H
#define TRAININGRESULTVIEW_H

#include <QWidget>
#include <QGraphicsItem>
#include <QGraphicsScene>

namespace Ui {
    class TrainingResultView;
}

class TrainingResultView : public QWidget {
Q_OBJECT

protected:
    // this event is called, when a new translator is loaded or the system language is changed
    void changeEvent(QEvent *) override;

public:
    explicit TrainingResultView(QWidget *parent = nullptr);

    TrainingResultView(QWidget *parent, QGraphicsItem *lossCurveImage, QGraphicsItem *matrixImage,
                       QList<QImage> images);

    ~TrainingResultView();

    void setLossCurve(QGraphicsItem *lossCurveImage);

    void setConfusionMatrix(QGraphicsItem *matrixImage);

    void setMostMisclassifiedImages(QList<QImage> images);

private:
    Ui::TrainingResultView *ui;
};

#endif // TRAININGRESULTVIEW_H
