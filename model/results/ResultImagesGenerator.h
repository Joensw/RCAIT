#ifndef RCAIT_RESULTIMAGESGENERATOR_H
#define RCAIT_RESULTIMAGESGENERATOR_H


#include <plugins/results/TrainingResult.h>
#include <plugins/results/ClassificationResult.h>
#include <QChartView>

class ResultImagesGenerator {
public:
    static QList<QImage> generateTrainingResultImages(TrainingResult* result);
    static QList<QImage> generateClassificationResultImages(ClassificationResult* result);

private:
    ResultImagesGenerator();

    static QImage generateLossCurveImage(QChartView* chart);
    //Todo: Find better way than transferring view pointer
    static QImage generateAccuracyImage(QChartView* chart);
};


#endif //RCAIT_RESULTIMAGESGENERATOR_H
