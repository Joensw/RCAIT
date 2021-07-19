#include <QFileInfo>
#include <QGraphicsSvgItem>
#include <QProcess>
#include "losscurve.h"

LossCurve::LossCurve(const QString &identifier, const QMap<int, QPair<double, double>> &data)
        : AbstractResultGraphics("losscurve_" + identifier, "svg") {
    m_data = data;
}

void LossCurve::generateGraphicsInternal(const QString &fullFilePath) {
    // python script.py <loss curve data> <output file name>
    auto pyScript = QFileInfo("losscurve.py");
    QStringList params = QStringList() << pyScript.absoluteFilePath() << valuesToPyText() << fullFilePath;
    AbstractResultGraphics::launch_externalGraphicsGenerator("python", params);
}

QString LossCurve::valuesToPyText() {
    auto result = new QStringList();

    for (const auto key: m_data.keys()) {
        auto &[train, val] = m_data[key];

        //Convert to QString with precision of 2 digits
        auto trainStr = QString::number(train, 'G', 5);
        auto valStr = QString::number(val, 'G', 5);

        //List for each row, which shall be joined in a single QString
        auto rowList = QStringList();
        rowList << QString::number(key) << trainStr << valStr;
        *result << '[' + rowList.join(',') + ']';
    }
    return '[' + result->join(',') + ']';
}

QPair<double, double> LossCurve::operator[](int epoch) const {
    return m_data[epoch];
}

bool LossCurve::operator==(const LossCurve &other) const {
    return m_data == other.m_data;
}

bool LossCurve::operator!=(const LossCurve &other) const {
    return m_data != other.m_data;
}

void LossCurve::passResultGraphics(const QString &fullFilePath, AbstractGraphicsView *receiver) {
    auto *graphics = new QGraphicsSvgItem(fullFilePath);
    receiver->setLossCurve(graphics);
}