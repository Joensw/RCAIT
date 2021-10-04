#include "result.h"

Result::Result(QString storageDir, QStringList additionalResults)
        : m_identifier(generateTimestamp()),
          m_storageDir(std::move(storageDir)),
          m_additionalResults(std::move(additionalResults)) {
}

QString Result::generateTimestamp() {
    auto date = QDateTime::currentDateTime();
    return date.toString("dd_MM_yy--hh-mm");
}

QString Result::generateExtendedTimestamp() {
    auto date = QDateTime::currentDateTime();
    return date.toString("dd_MM_yy--hh-mm-ss");
}

QString Result::niceRepresentation(QString date) {
    date.replace("_", ".");
    date.replace("--", " — ");
    date.replace("-", ":");
    return date;
}

QString Result::savableRepresentation(QString date) {
    date.replace(".", "_");
    date.replace(" — ", "--");
    date.replace(":", "-");
    return date;
}

[[maybe_unused]] QStringList Result::getAdditionalResults() const {
    return m_additionalResults;
}

[[maybe_unused]] QString Result::getIdentifier() const {
    return Result::niceRepresentation(m_identifier);
}

[[maybe_unused]] QString Result::getSavableIdentifier() const {
    return Result::savableRepresentation(m_identifier);
}

[[maybe_unused]] const QString &Result::getStorageDir() const {
    return m_storageDir;
}
