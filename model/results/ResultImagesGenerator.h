#ifndef RCAIT_RESULTIMAGESGENERATOR_H
#define RCAIT_RESULTIMAGESGENERATOR_H


#include <plugins/results/TrainingResult.h>
#include <plugins/results/ClassificationResult.h>
#include <QChartView>

class ResultImagesGenerator {
public:
    ResultImagesGenerator();
    //Todo: QImages Lists are weird
    QList<QImage> generateTrainingResultImages(TrainingResult* result);
    QList<QImage> generateClassificationResultImages(ClassificationResult* result);

private:
    QImage generateLossCurveImage(QChartView* chart);
    //Todo: Find better way than transferring view pointer
    QImage generateAccuracyImage(QChartView* chart);
};


#endif //RCAIT_RESULTIMAGESGENERATOR_H
