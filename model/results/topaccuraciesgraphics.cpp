#include <QFileInfo>
#include "topaccuraciesgraphics.h"

TopAccuraciesGraphics::TopAccuraciesGraphics(const QString &identifier,
                                             const QMap<QString, QPair<double, double>> &data)
        : AbstractResultGraphics("topaccuracies_" + identifier, "svg") {

    m_data = data;
}

QString TopAccuraciesGraphics::valuesToPyText() {
    auto result = new QStringList();

    for (auto &[top1, top5]: m_data) {
        //Convert to QString with precision of 2 digits
        auto top1Str = QString::number(top1, 'G', 5);
        auto top5Str = QString::number(top5, 'G', 5);

        //List for each row, which shall be joined in a single QString
        auto rowList = QStringList();
        rowList << top1Str << top5Str;
        *result << '[' + rowList.join(',') + ']';
    }
    return '[' + result->join(',') + ']';
}

QString TopAccuraciesGraphics::labelsToPyText() {
    QStringList results;
    for (const auto &key : m_data.keys()) {
        results << QString("'%1'").arg(key);
    }
    return '[' + results.join(',') + ']';
}

void TopAccuraciesGraphics::addDataRow(const QString &identifier, double top1, double top5) {
    m_data.insert(identifier, qMakePair(top1, top5));
}

void TopAccuraciesGraphics::removeDataRow(const QString &identifier) {
    m_data.remove(identifier);
}

QPair<double, double> TopAccuraciesGraphics::operator[](const QString &identifier) const {
    return m_data[identifier];
}

bool TopAccuraciesGraphics::operator==(const TopAccuraciesGraphics &other) const {
    return (m_data == other.m_data);
}

bool TopAccuraciesGraphics::operator!=(const TopAccuraciesGraphics &other) const {
    return (m_data != other.m_data);
}

void TopAccuraciesGraphics::generateGraphicsInternal(const QString &fullFilePath) {
    // python script.py <loss curve data> <output file name>
    auto pyScript = QFileInfo("topaccuraciesgraphics.py");
    QStringList params = QStringList() << pyScript.absoluteFilePath() << valuesToPyText() << labelsToPyText() <<fullFilePath;
    AbstractResultGraphics::launch_externalGraphicsGenerator("python", params);
}

void TopAccuraciesGraphics::passResultGraphics(const QString &fullFilePath, AbstractGraphicsView *receiver) {
    auto *graphics = new QGraphicsSvgItem(fullFilePath);
    receiver->setTopAccuraciesGraphics(graphics);
}
