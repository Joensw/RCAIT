#include <QDateTime>
#include <utility>
#include "result.h"

Result::Result(QStringList additionalResults) : m_additionalResults(std::move(additionalResults)){
    m_identifier = generateTimestamp();
}

QString Result::generateTimestamp() {
    auto date = QDateTime::currentDateTime();
    return date.toString("dd_MM_yy--hh-mm");
}

QString Result::generateExtendedTimestamp() {
    auto date = QDateTime::currentDateTime();
    return date.toString("dd_MM_yy--hh-mm-ss");
}

QString Result::niceRepresentation(QString date){
    date.replace("_",".");
    date.replace("--"," — ");
    date.replace("-",":");
    return date;
}

QString Result::savableRepresentation(QString date){
    date.replace(".","_");
    date.replace(" — ","--");
    date.replace(":","-");
    return date;
}

QStringList Result::getAdditionalResults() const {
    return m_additionalResults;
}

QString Result::getIdentifier() const{
    return Result::niceRepresentation(m_identifier);
}

QString Result::getSavableIdentifier() const{
    return Result::savableRepresentation(m_identifier);
}