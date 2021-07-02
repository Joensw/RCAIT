#include "ResultImagesGenerator.h"

ResultImagesGenerator::ResultImagesGenerator() {

}

QList<QImage> ResultImagesGenerator::generateTrainingResultImages(TrainingResult *result) {
    return QList<QImage>();
}

QList<QImage> ResultImagesGenerator::generateClassificationResultImages(ClassificationResult *result) {
    return QList<QImage>();
}

QImage ResultImagesGenerator::generateConfusionMatrixImage(QAbstractTableModel matrix, QStringList labels) {
    return QImage();
}

QImage ResultImagesGenerator::generateLossCurveImage(QMap<int, QVector<double>>) {
    return QImage();
}

QImage ResultImagesGenerator::generateAccuracyImage(double top1, double top5) {
    return QImage();
}

QImage
ResultImagesGenerator::generateClassificationTableImage(QMap<QString, QVector<double>> table, QVector<QString> labels) {
    return QImage();
}
