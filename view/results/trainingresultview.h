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
    explicit TrainingResultView(SavableResultsWidget *tabWidget, QWidget *parent = nullptr);

    void setAccuracyCurve(const QSharedPointer<QGraphicsItem> &accuracyCurveImage) override;

    void setConfusionMatrix(const QSharedPointer<QGraphicsItem> &matrixImage) override;

    void setMostMisclassifiedImages(const QStringList &images);

    [[maybe_unused]] [[nodiscard]] const QSharedPointer<QGraphicsItem> &getAccuracyCurveImage() const;

    [[maybe_unused]] [[nodiscard]] const QSharedPointer<QGraphicsItem> &getConfusionMatrixImage() const;

    ~TrainingResultView() override;

private:
    static constexpr auto IMAGES_GRID_SIZE = 3;
    static constexpr auto ACCURACY_CURVE_SCALING_FACTOR = 0.9;
    static constexpr auto CONFUSIONMATRIX_SCALING_FACTOR = 0.85;

    Ui::TrainingResultView *ui;

    QSharedPointer<QGraphicsItem> m_accuracyCurveImage;
    QSharedPointer<QGraphicsItem> m_confusionMatrixImage;
    QScopedPointer<QGraphicsScene> m_accuracyCurveScene;
    QScopedPointer<QGraphicsScene> m_confusionMatrixScene;
};

#endif // TRAININGRESULTVIEW_H
