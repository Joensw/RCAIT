#include <QFileInfo>
#include <QGraphicsSvgItem>
#include <QProcess>
#include "losscurve.h"

LossCurve::LossCurve(const QString &identifier, const QMap<int, QPair<double, double>> &data)
        : AbstractResultGraphics("losscurve_" + identifier, "svg") {
    m_data = data;
}

void LossCurve::generateGraphicsInternal(const QString &fullFilePath) {
    //Call python script
    auto file = QFileInfo("losscurve.py");
    QString path = file.absolutePath();
    QString command("python");

    // python script.py <loss curve data> <output file name>
    QStringList params = QStringList() << file.absoluteFilePath() << valuesToPyText() << fullFilePath;
    auto *process = new QProcess();

    process->start(command, params);
    process->waitForStarted();
    process->waitForFinished();

    QString strTemp = QString::fromLocal8Bit(process->readAll());  // Get the output
    qInfo() << qPrintable(strTemp.simplified());

    process->close();
}

QString LossCurve::valuesToPyText() {
    auto result = new QStringList();
    for (const auto key: m_data.keys()) {
        auto rowList = QStringList();
        auto &[train, val] = m_data[key];

        //Convert to QString with precision of 2 digits
        auto trainStr = QString::number(train, 'G', 5);
        auto valStr = QString::number(val, 'G', 5);
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

void LossCurve::passResultGraphics(const QString &fullFilePath, TrainingResultView *receiver) {
    auto *graphics = new QGraphicsSvgItem(fullFilePath);
    receiver->setLossCurve(graphics);
}
