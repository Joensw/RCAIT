#include "ResultImagesGenerator.h"

ResultImagesGenerator::ResultImagesGenerator() = default;

QList<QImage> ResultImagesGenerator::generateTrainingResultImages(TrainingResult *result) {
    return QList<QImage>();
}

QList<QImage> ResultImagesGenerator::generateClassificationResultImages(ClassificationResult *result) {
    return QList<QImage>();
}

QImage ResultImagesGenerator::generateLossCurveImage(QChartView *chart) {
    return QImage();
}

QImage ResultImagesGenerator::generateAccuracyImage(QChartView *chart) {
    return QImage();
}
