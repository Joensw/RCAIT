#include <QString>
#include <QFileInfo>
#include <mapadapt.h>
#include "classificationgraphics.h"

ClassificationGraphics::ClassificationGraphics(const QString &directory, const QString &identifier,
                                               const QMap<QString, QList<double>> &data)
        : AbstractResultGraphics(directory, "classification_" + identifier, "svg") {

    m_data = data;
}

QString ClassificationGraphics::valuesToPyText() {
    auto result = QStringList();

    for (const auto &row_data: m_data) {
        //List for each row, which shall be joined in a single QString
        auto rowList = QStringList();

        //Convert to QString with precision of 2 digits
        for (const auto &value : row_data) {
            auto valueStr = QString::number(value, 'f', 2);
            rowList << valueStr;
        }
        result << '[' + rowList.join(',') + ']';
    }
    return '[' + result.join(',') + ']';
}

QString ClassificationGraphics::labelsToPyText() {
    auto results = QStringList();
    for (const auto& [key,_]: MapAdapt(m_data)) {
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
    // python script.py <classification data> <classification labels> <output file name>
    auto pyScript = QFileInfo("classificationgraphics.py");
    QStringList params =
            QStringList() << pyScript.absoluteFilePath() << valuesToPyText() << labelsToPyText() << fullFilePath;
    AbstractResultGraphics::launch_externalGraphicsGenerator("python", params);
}

void ClassificationGraphics::passResultGraphics(const QString &fullFilePath, AbstractGraphicsView *receiver) {
    auto *graphics = new QGraphicsSvgItem(fullFilePath);
    auto ptr = QSharedPointer<QGraphicsItem>(graphics);
    receiver->setClassificationGraphics(ptr);
}