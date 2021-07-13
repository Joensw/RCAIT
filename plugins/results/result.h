#ifndef RESULT_H
#define RESULT_H


#include <QImage>

class Result {
private:
    QList<QImage> m_additionalResults;
    QString m_timestamp;

public:
    explicit Result(const QList<QImage>& additionalResults = QList<QImage>());
    [[nodiscard]] QList<QImage> getAdditionalResults();

    [[nodiscard]] QString getTimestamp();
};


#endif //RCAIT_RESULT_H
