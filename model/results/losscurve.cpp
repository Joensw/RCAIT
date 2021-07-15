#include <QFileInfo>
#include <QGraphicsSvgItem>
#include <QProcess>
#include "losscurve.h"

LossCurve::LossCurve(const QMap<int, QPair<double, double>> &data) {
    m_data = data;
}

QGraphicsItem *LossCurve::generateLossCurveGraphics(const QString &fileName) {
    //Call python script
    auto file = QFileInfo("losscurve.py");
    QString path = file.absolutePath();
    QString command("python");

    // python script.py <loss curve data> <output file name>
    QStringList params = QStringList() << file.absoluteFilePath() << valuesToPyText() << fileName;
    auto *process = new QProcess();

    process->start(command,params);
    process->waitForStarted();
    process->waitForFinished();

    QString strTemp = QString::fromLocal8Bit(process->readAll());  // Get the output
    qInfo() << qPrintable(strTemp.simplified());

    process->close();

    return new QGraphicsSvgItem(path + "/" + fileName);
}

QString LossCurve::valuesToPyText() {
    auto result = new QStringList();
    for (const auto key: m_data.keys()) {
        auto rowList = QStringList();
        auto &[train, val] = m_data[key];
        rowList << QString::number(key) << QString::number(train) << QString::number(val);
        *result << '[' + rowList.join(',') + ']';
    }
    return '[' + result->join(',') + ']';
}

QPair<double, double> LossCurve::operator[](int epoch) const {
    return m_data[epoch];
}

bool LossCurve::operator==(const LossCurve& other) const {
    return m_data == other.m_data;
}

bool LossCurve::operator!=(const LossCurve& other) const {
    return m_data != other.m_data;
}
