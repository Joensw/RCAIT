#ifndef TRAININGRESULTVIEW_H
#define TRAININGRESULTVIEW_H

#include <QWidget>
#include <QGraphicsItem>
#include <QGraphicsScene>
#include "genericgraphicsview.h"

namespace Ui {
    class TrainingResultView;
}

class TrainingResultView : public GenericGraphicsView {

protected:
    // this event is called, when a new translator is loaded or the system language is changed
    void changeEvent(QEvent *) override;

public:
    explicit TrainingResultView(QWidget *parent = nullptr);

    void setAccuracyCurve(const QSharedPointer<QGraphicsItem> &accuracyCurveImage) override;

    void setConfusionMatrix(const QSharedPointer<QGraphicsItem> &matrixImage) override;

    void setMostMisclassifiedImages(const QStringList& images);

    [[nodiscard]] const QSharedPointer<QGraphicsItem> &getAccuracyCurveImage() const;

    [[nodiscard]] const QSharedPointer<QGraphicsItem> &getConfusionMatrixImage() const;

    ~TrainingResultView() override;

private:
    Ui::TrainingResultView *ui;

    QSharedPointer<QGraphicsItem> m_accuracyCurveImage;
    QSharedPointer<QGraphicsItem> m_confusionMatrixImage;
};

#endif // TRAININGRESULTVIEW_H
