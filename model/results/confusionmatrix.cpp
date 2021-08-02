#include "confusionmatrix.h"


ConfusionMatrix::ConfusionMatrix(const QString &identifier, const QStringList &classLabels,
                                 const QList<int> &values)
        : AbstractResultGraphics("confusionmatrix_" + identifier, "svg"), m_size(classLabels.size()) {

    Q_ASSERT(!classLabels.isEmpty());
    Q_ASSERT(!values.isEmpty());
    Q_ASSERT(classLabels.size() * classLabels.size() == values.size());
    m_classLabels = classLabels;
    m_values = values;
}


void ConfusionMatrix::generateGraphicsInternal(const QString &fullFilePath) {
    // python script.py <matrix data> <matrix labels> <output file name> (<normalized>)
    auto file = QFileInfo("confusionmatrix.py");
    QStringList params =
            QStringList() << file.absoluteFilePath() << valuesToPyText() << labelsToPyText() << fullFilePath
                          << "--normalized";
    AbstractResultGraphics::launch_externalGraphicsGenerator("python", params);
}

/**
 * Access matrix via matrix(row,column) operator
 * @return value of matrix at(row,column)
 */
double ConfusionMatrix::operator()(int row, int column) const {
    Q_ASSERT(row >= 0 && row < m_size && column >= 0 && column < m_size);
    return m_values[row * m_size + column];
}

/**
 * Convert matrix labels to text in a python-friendly way
 * @return QString label representation e.g. ["Car","Truck"]
 */
QString ConfusionMatrix::labelsToPyText() {
    QStringList labels = QStringList();
    for (auto &item : m_classLabels) {
        labels << '"' + item + '"';
    }
    return '[' + labels.join(',') + ']';
}

/**
 * Convert matrix data to text in a python-friendly way
 * @return QString matrix representation e.g. [[1,2],[3,4]]
 */
QString ConfusionMatrix::valuesToPyText() {
    auto result = QStringList();
    for (qsizetype row = 0; row < m_size; row++) {
        auto rowList = new QStringList();
        for (qsizetype col = 0; col < m_size; col++) {
            *rowList << QString::number(m_values[row * m_size + col]);
        }
        result << '[' + rowList->join(',') + ']';
    }
    return '[' + result.join(',') + ']';
}

bool ConfusionMatrix::operator==(const ConfusionMatrix other) const {
    if (m_classLabels != other.m_classLabels) return false;
    if (m_size != other.m_size) return false;

    for (int row = 0; row < m_size; ++row)
        for (int col = 0; col < m_size; ++col) {
            if (m_values[row * m_size + col] != other.m_values[row * m_size + col])
                return false;
        }
    return true;
}

bool ConfusionMatrix::operator!=(const ConfusionMatrix other) const {
    return !(*this == other);
}

QStringList ConfusionMatrix::getClassLabels()
{
    return m_classLabels;
}

QList<int> ConfusionMatrix::getValues()
{
    return m_values;
}

void ConfusionMatrix::passResultGraphics(const QString &fullFilePath, AbstractGraphicsView *receiver) {
    auto *graphics = new QGraphicsSvgItem(fullFilePath);
    receiver->setConfusionMatrix(graphics);
}

