#ifndef TRAININGRESULTVIEW_H
#define TRAININGRESULTVIEW_H

#include <QWidget>
#include <QGraphicsItem>
#include <QGraphicsScene>
#include <genericgraphicsview.h>

namespace Ui {
    class TrainingResultView;
}

/**
 * @brief This class is a view wrapper for training results.
 * This is used as tabs in a TrainingResultsWidget.
 */
class TrainingResultView : public GenericGraphicsView {

protected:
    /**
     * @brief this event is called, when a new translator is loaded or the system language is changed
     */
    void changeEvent(QEvent *) override;

public:
    /**
     * @brief Constructs a TrainingResultView.
     * @param tabWidget TabWidget parent which will hold this object
     * @param parent QWidget parent (optional)
     */
    explicit TrainingResultView(SavableResultsWidget *tabWidget, QWidget *parent = nullptr);

    /**
     * @brief Sets the accuracy curve
     * @param accuracyCurveImage QSharedPointer to the accuracy curve image
     */
    void setAccuracyCurve(const QSharedPointer<QGraphicsItem> &accuracyCurveImage) override;

    /**
    * @brief Sets the confusion matrix image
    * @param matrixImage QSharedPointer to the confusion matrix image
    */
    void setConfusionMatrix(const QSharedPointer<QGraphicsItem> &matrixImage) override;

    /**
     * @brief Sets the most misclassified images
     * @param images List of paths to most misclassified images.
     */
    void setMostMisclassifiedImages(const QStringList &images);

    /**
     * @brief Get the current accuracy curve graphics
     * @return QSharedPointer pointing to the graphics
     */
    [[maybe_unused]] [[nodiscard]] const QSharedPointer<QGraphicsItem> &getAccuracyCurveImage() const;

    /**
     * @brief Get the current confusion matrix graphics
     * @return QSharedPointer pointing to the graphics
     */
    [[maybe_unused]] [[nodiscard]] const QSharedPointer<QGraphicsItem> &getConfusionMatrixImage() const;

    /**
     * @brief Destructor for this class
     */
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
