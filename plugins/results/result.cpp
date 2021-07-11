#include <QDateTime>
#include "result.h"

Result::Result(const QList<QImage> &additionalResults) {
    m_additionalResults = additionalResults;
    auto date = QDateTime::currentDateTime();
    m_timestamp = date.toString("dd_MM_yy+hh-mm");
}

QList<QImage> Result::getAdditionalResults() {
    return m_additionalResults;
}

QString Result::getTimestamp() {
    return m_timestamp;
}
