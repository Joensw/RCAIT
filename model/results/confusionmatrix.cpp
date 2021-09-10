#include "confusionmatrix.h"


ConfusionMatrix::ConfusionMatrix(const QString &directory,
                                 const QString &identifier,
                                 const QStringList &classLabels,
                                 const QList<int> &values)
        : GenericResultGraphics(directory, "confusionmatrix_" % identifier, "svg"),
          m_size(classLabels.size()),
          m_classLabels(classLabels),
          m_values(values) {

    if (classLabels.isEmpty()) {
        qWarning() << "Confusion Matrix has no labels";
    }
    if (values.isEmpty()) {
        qWarning() << "Confusion Matrix has no values";
    }
    if (classLabels.size() * classLabels.size() != values.size()) {
        qWarning() << "Confusion Matrix must be a square Matrix of dimension: number of labels x number of labels";
    }
}


void ConfusionMatrix::generateGraphicsInternal(const QString &fullFilePath) {
    // python script.py <matrix data> <matrix labels> <output file name> (<normalized>)
    auto file = QFileInfo("confusionmatrix.py");
    QStringList params =
            QStringList() << file.absoluteFilePath() << valuesToPyText() << labelsToPyText() << fullFilePath
                          << "--normalized";
    GenericResultGraphics::launch_externalGraphicsGenerator("python", params);
}

double ConfusionMatrix::operator()(int row, int column) const {
    Q_ASSERT(row >= 0 && row < m_size && column >= 0 && column < m_size);
    return m_values[row * m_size + column];
}

QString ConfusionMatrix::labelsToPyText() {
    QStringList labels;
    for (auto &item : m_classLabels) {
        labels << "'" % item % "'";
    }
    //Add "" around string so that dashes are not recognized as new arguments
    return '"' % ('[' % labels.join(',') % ']') % '"';
}

QString ConfusionMatrix::valuesToPyText() {
    QStringList result;
    for (qsizetype row = 0; row < m_size; row++) {
        QStringList rowList;
        for (qsizetype col = 0; col < m_size; col++) {
            rowList << QString::number(m_values[row * m_size + col]);
        }
        result << '[' % rowList.join(',') % ']';
    }
    return '[' % result.join(',') % ']';
}

bool ConfusionMatrix::operator==(const ConfusionMatrix &other) const {
    if (m_classLabels != other.m_classLabels) return false;
    if (m_size != other.m_size) return false;

    for (int row = 0; row < m_size; ++row)
        for (int col = 0; col < m_size; ++col) {
            if (m_values[row * m_size + col] != other.m_values[row * m_size + col])
                return false;
        }
    return true;
}

bool ConfusionMatrix::operator!=(const ConfusionMatrix& other) const {
    return !(*this == other);
}

[[maybe_unused]] const QStringList &ConfusionMatrix::getClassLabels() const {
    return m_classLabels;
}

[[maybe_unused]] qsizetype ConfusionMatrix::getSize() const {
    return m_size;
}

[[maybe_unused]] const QList<int> &ConfusionMatrix::getValues() const {
    return m_values;
}

void ConfusionMatrix::passResultGraphics(GenericGraphicsView *receiver, const QString &fullFilePath) {
    auto *graphics = new QGraphicsSvgItem(fullFilePath);
    auto ptr = QSharedPointer<QGraphicsItem>(graphics);
    receiver->setConfusionMatrix(ptr);
}
