#include <QFileInfo>
#include "topaccuraciesgraphics.h"

TopAccuraciesGraphics::TopAccuraciesGraphics(const QString &directory,
                                             const QList<QPair<QString, QList<double>>> &data)
        : GenericResultGraphics(directory, "topaccuracies", "svg"),
          m_data(data) {
}

QString TopAccuraciesGraphics::valuesToPyText() {
    QStringList result;

    for (auto &[key, valuesList]: m_data) {
        //List for each row, which shall be joined in a single QString
        QStringList rowList;

        for (const auto &value : valuesList) {
            //Convert to QString with precision of 2 digits
            rowList << QString::number(value, 'f', 2);
        }
        result << '[' % rowList.join(',') % ']';
    }
    return '[' % result.join(',') % ']';
}

QString TopAccuraciesGraphics::labelsToPyText() {
    QStringList results;
    for (const auto &[key, _] : m_data) {
        results << "'" % key % "'";
    }
    //Add "" around string so that dashes are not recognized as new arguments
    return '"' % ('[' % results.join(',') % ']') % '"';
}

void TopAccuraciesGraphics::addDataRow(const QString &identifier, const QList<double> &data) {
    m_data << qMakePair(identifier, data);
}

void TopAccuraciesGraphics::removeDataRow(const QString &identifier) {
    auto index = 0;
    for (const auto &[key, _] : m_data) {
        if (key == identifier) {
            m_data.remove(index);
            return;
        }
        index++;
    }
}

QList<double> TopAccuraciesGraphics::operator[](const QString &identifier) const {
    for (const auto &[key, valuesList] : m_data) {
        if (key == identifier)
            return valuesList;
    }
    return {};
}

[[maybe_unused]] void TopAccuraciesGraphics::setData(const QList<QPair<QString, QList<double>>> &mData) {
    m_data = mData;
}

bool TopAccuraciesGraphics::operator==(const TopAccuraciesGraphics &other) const {
    return (m_data == other.m_data);
}

bool TopAccuraciesGraphics::operator!=(const TopAccuraciesGraphics &other) const {
    return (m_data != other.m_data);
}

void TopAccuraciesGraphics::generateGraphicsInternal(const QString &fullFilePath) {
    // python script.py <top acc data> <top acc row labels> <output file name>
    auto pyScript = QFileInfo("topaccuraciesgraphics.py");
    QStringList params =
            QStringList() << pyScript.absoluteFilePath() << valuesToPyText() << labelsToPyText() << fullFilePath;
    GenericResultGraphics::launch_externalGraphicsGenerator("python", params);
}

void TopAccuraciesGraphics::passResultGraphics(const QString &fullFilePath, GenericGraphicsView *receiver) {
    auto *graphics = new QGraphicsSvgItem(fullFilePath);
    auto ptr = QSharedPointer<QGraphicsItem>(graphics);
    receiver->setTopAccuraciesGraphics(ptr);
}
