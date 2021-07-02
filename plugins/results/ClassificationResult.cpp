#include "ClassificationResult.h"
#include <utility>

ClassificationResult::ClassificationResult(QList<QImage> additionalResult, QMap<QString, QVector<double>> table,
                                           QVector<QString> labels, QList<QImage> additionalResults)
        : Result(std::move(additionalResult)) {

}

QAbstractTableModel *ClassificationResult::getTable() {
    return nullptr;
}

QVector<QString> ClassificationResult::getLabel() {
    return QVector<QString>();
}
