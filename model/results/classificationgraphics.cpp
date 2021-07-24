#include <QString>
#include <QFileInfo>
#include "classificationgraphics.h"

ClassificationGraphics::ClassificationGraphics(const QString &identifier,
                                               const QMap<QString, QList<double>> &data)
        : AbstractResultGraphics("classificationgraphics_" + identifier, "svg") {

    m_data = data;
}

QString ClassificationGraphics::valuesToPyText() {
    auto result = new QStringList();

    for (const auto &row_data: m_data) {
        //List for each row, which shall be joined in a single QString
        auto rowList = QStringList();

        //Convert to QString with precision of 2 digits
        for (const auto &value : row_data) {
            auto valueStr = QString::number(value, 'G', 5);
            rowList << valueStr;
        }
        *result << '[' + rowList.join(',') + ']';
    }
    return '[' + result->join(',') + ']';
}

QString ClassificationGraphics::labelsToPyText() {
    QStringList results;
    for (const auto &key : m_data.keys()) {
        results << QString("'%1'").arg(key);
    }
    return '[' + results.join(',') + ']';
}

void ClassificationGraphics::addDataRow(const QString &identifier, QList<double> &data) {
    m_data.insert(identifier, data);
}

void ClassificationGraphics::removeDataRow(const QString &identifier) {
    m_data.remove(identifier);
}

QList<double> ClassificationGraphics::operator[](const QString &identifier) const {
    return m_data[identifier];
}

bool ClassificationGraphics::operator==(const ClassificationGraphics &other) const {
    return (m_data == other.m_data);
}

bool ClassificationGraphics::operator!=(const ClassificationGraphics &other) const {
    return (m_data != other.m_data);
}

void ClassificationGraphics::generateGraphicsInternal(const QString &fullFilePath) {
    // python script.py <loss curve data> <output file name>
    auto pyScript = QFileInfo("classificationgraphics.py");
    QStringList params =
            QStringList() << pyScript.absoluteFilePath() << valuesToPyText() << labelsToPyText() << fullFilePath;
    AbstractResultGraphics::launch_externalGraphicsGenerator("python", params);
}

void ClassificationGraphics::passResultGraphics(const QString &fullFilePath, AbstractGraphicsView *receiver) {
    auto *graphics = new QGraphicsSvgItem(fullFilePath);
    receiver->setClassificationGraphics(graphics);
}