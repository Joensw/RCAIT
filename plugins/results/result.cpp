#include <QDateTime>
#include <utility>
#include "result.h"

Result::Result(QStringList additionalResults) : m_additionalResults(std::move(additionalResults)){
    m_identifier = generateIdentifier();
}

QString Result::generateIdentifier() {
    auto date = QDateTime::currentDateTime();
    return date.toString("dd_MM_yy#hh-mm");
}

QStringList Result::getAdditionalResults() const {
    return m_additionalResults;
}

QString Result::getIdentifier() const{
    return m_identifier;
}
