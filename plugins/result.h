#ifndef RESULT_H
#define RESULT_H

#include <QImage>



class Result
{
public:
    Result();
    Result(QList<QImage> additionalResult);
    QList<QImage> getAdditionalResults();

private:
    QList<QImage> additionalResults;
};

#endif // RESULT_H
