#include <QFileInfo>
#include "topaccuraciesgraphics.h"

TopAccuraciesGraphics::TopAccuraciesGraphics(const QString &identifier,
                                             const QList<QPair<QString, QList<double>>> &data)
        : AbstractResultGraphics("topaccuracies_" + identifier, "svg") {

    m_data = data;
}

QString TopAccuraciesGraphics::valuesToPyText() {
    auto result = new QStringList();

    for (auto &[key, valuesList]: m_data) {

        //List for each row, which shall be joined in a single QString
        auto rowList = QStringList();
        for (const auto &value : valuesList){
            //Convert to QString with precision of 2 digits
            auto valStr = QString::number(value, 'G', 5);
            rowList << valStr;

        }
        *result << '[' + rowList.join(',') + ']';
    }
    return '[' + result->join(',') + ']';
}

QString TopAccuraciesGraphics::labelsToPyText() {
    auto results = QStringList();
    for (const auto &[key, _] : m_data) {
        results << QString("'%1'").arg(key);
    }
    return '[' + results.join(',') + ']';
}

void TopAccuraciesGraphics::addDataRow(const QString &identifier, const QList<double> &data) {
    auto pair = qMakePair(identifier, data);
    m_data.append(pair);
}

void TopAccuraciesGraphics::removeDataRow(const QString &identifier) {
    auto index = 0;
    for (const auto &[key, _] : m_data){
        if (key == identifier){
            m_data.remove(index);
            return;
        }
        index++;
    }
}

QList<double> TopAccuraciesGraphics::operator[](const QString &identifier) const {
    for (const auto &[key, valuesList] : m_data){
        if (key == identifier)
            return valuesList;
    }
    return QList<double>();
}

void TopAccuraciesGraphics::setData(const QList<QPair<QString, QList<double>>> &mData) {
    m_data = mData;
}

bool TopAccuraciesGraphics::operator==(const TopAccuraciesGraphics &other) const {
    return (m_data == other.m_data);
}

bool TopAccuraciesGraphics::operator!=(const TopAccuraciesGraphics &other) const {
    return (m_data != other.m_data);
}

void TopAccuraciesGraphics::generateGraphicsInternal(const QString &fullFilePath) {
    //TODO Update description
    // python script.py <loss curve data> <output file name>
    auto pyScript = QFileInfo("topaccuraciesgraphics.py");
    QStringList params = QStringList() << pyScript.absoluteFilePath() << valuesToPyText() << labelsToPyText() <<fullFilePath;
    AbstractResultGraphics::launch_externalGraphicsGenerator("python", params);
}

void TopAccuraciesGraphics::passResultGraphics(const QString &fullFilePath, AbstractGraphicsView *receiver) {
    auto *graphics = new QGraphicsSvgItem(fullFilePath);
    receiver->setTopAccuraciesGraphics(graphics);
}
