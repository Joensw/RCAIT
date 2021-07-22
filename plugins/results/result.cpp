#include <QDateTime>
#include "result.h"

Result::Result(const QList<QImage> &additionalResults) {
    m_additionalResults = additionalResults;
    m_timestamp = generateIdentifier();
}

QString Result::generateIdentifier(){
    auto date = QDateTime::currentDateTime();
    return date.toString("dd_MM_yy#hh-mm-ss");
}

QList<QImage> Result::getAdditionalResults() {
    return m_additionalResults;
}

QString Result::getTimestamp() {
    return m_timestamp;
}
