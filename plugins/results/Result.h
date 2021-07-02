#ifndef RCAIT_RESULT_H
#define RCAIT_RESULT_H


#include <QImage>

class Result {
private:
    QList<QImage> additionalResults;
public:
    Result(QList<QImage> additionalResult);
    QList<QImage> getAdditionalResults();
};


#endif //RCAIT_RESULT_H
