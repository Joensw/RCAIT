#ifndef TRAININGRESULT_H
#define TRAININGRESULT_H


#include <confusionmatrix.h>
#include <accuracycurve.h>
#include "result.h"

/**
 * @brief This class is a specific type of <code>Result</code>.
 * It is also a data retention class and holds all data after a training process.
 */
class TrainingResult : public Result {
private:
    QStringList m_mostMisclassifiedImages;
    QMap<int, QPair<double, double>> m_accuracyCurveData;
    QStringList m_classLabels;
    QList<int> m_confusionMatrixValues;
    QSharedPointer<AccuracyCurve> m_accCurve;
    QSharedPointer<ConfusionMatrix> m_confusionMatrix;
    double m_top1Accuracy;
    double m_top5Accuracy;

    TrainingResult(const TrainingResult &) = delete;

    TrainingResult &operator=(const TrainingResult &) = delete;

public:
    /**
     * @brief Constructs a TrainingResult.
     * @param storageDir passed to parent, must be a directory path
     * @param accuracyCurveData data points to construct an <code>AccuracyCurve</code>
     * @param classLabels list of class labels
     * @param confusionMatrixValues values of the <code>ConfusionMatrix</code>
     * @param mostMisclassifiedImages list of the most misclassified images
     * @param top1Accuracy top1 accuracy score
     * @param top5Accuracy top5 accuracy score
     * @param additionalResults (Optional) List of paths to additional results.
     */
    TrainingResult(const QString &storageDir, const QMap<int, QPair<double, double>> &accuracyCurveData,
                   const QStringList &classLabels, const QList<int> &confusionMatrixValues,
                   QStringList mostMisclassifiedImages, double top1Accuracy, double top5Accuracy,
                   const QStringList &additionalResults = {});

    /**
     * @brief Get the accuracy curve.
     * @return shared pointer to the <code>AccuracyCurve</code> of this result
     */
    [[nodiscard]] const QSharedPointer<AccuracyCurve> &getAccuracyCurve() const;

    /**
     * @brief Get the confusion matrix.
     * @return shared pointer to the <code>ConfusionMatrix</code> of this result.
     */
    [[nodiscard]] const QSharedPointer<ConfusionMatrix> &getConfusionMatrix() const;

    /**
     * @brief Gets the top 1 accuracy score of this result
     * @return top 1 accuracy score as double
     */
    [[nodiscard]] double getTop1Accuracy() const;

    /**
     * @brief Gets the top 5 accuracy score of this result
     * @return top 5 accuracy score as double
     */
    [[nodiscard]] double getTop5Accuracy() const;

    /**
     * @brief Gets a list of the most misclassified images.
     * @return List of the most misclassified images.
     */
    [[nodiscard]] QStringList getMostMisclassifiedImages() const;

    /**
     * @brief Gets the data of the accuracy curve.
     * @return map of accuracy curve data.
     */
    [[nodiscard]] const QMap<int, QPair<double, double>> &getAccuracyCurveData() const;

    /**
     * @brief Get the class labels.
     * @return list of class labels.
     */
    [[nodiscard]] const QStringList &getClassLabels() const;

    /**
     * @brief Gets the values of the confusion matrix.
     * @return list of the values of the confusion matrix.
     */
    [[nodiscard]] const QList<int> &getConfusionMatrixValues() const;

    /**
     * @brief Checks if this result is valid.
     * @return valid or not.
     */
    bool isValid() const;

};


#endif //TRAININGRESULT_H
