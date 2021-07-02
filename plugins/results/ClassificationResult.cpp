#include "ClassificationResult.h"

ClassificationResult::ClassificationResult(QMap<QString, QVector<double>> table, QVector<QString> labels,
                                           QList<QImage> additionalResults) {

}

QAbstractTableModel *ClassificationResult::getTable() {
    return nullptr;
}

QVector<QString> ClassificationResult::getLabel() {
    return QVector<QString>();
}
