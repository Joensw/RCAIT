#include "accuracycurve.h"

AccuracyCurve::AccuracyCurve(const QString &directory, const QString &identifier,
                             const QMap<int, QPair<double, double>> &data)
        : GenericResultGraphics(directory, "accuracycurve_" % identifier, "svg"),
          m_data(data) {
}

void AccuracyCurve::generateGraphicsInternal(const QString &fullFilePath) {
    // python script.py <acc curve data> <output file name>
    auto pyScript = QFileInfo("accuracycurve.py");
    auto params = {pyScript.absoluteFilePath(), valuesToPyText(), fullFilePath};
    auto command = ConfigurationManager::getInstance().getPythonExecutablePath();
    GenericResultGraphics::launch_externalGraphicsGenerator(command, params);
}

QString AccuracyCurve::valuesToPyText() {
    QStringList result;

    for (const auto&[key, _]: MapAdapt(m_data)) {
        auto &[train, val] = m_data[key];

        //Convert to QString with precision of 2 digits
        auto trainStr = QString::number(train, 'f', 2);
        auto valStr = QString::number(val, 'f', 2);

        //List for each row, which shall be joined in a single QString
        QStringList rowList;
        rowList << QString::number(key) << trainStr << valStr;
        result << '[' % rowList.join(',') % ']';
    }
    return '[' % result.join(',') % ']';
}

QPair<double, double> AccuracyCurve::operator[](int iteration) const {
    return m_data[iteration];
}

bool AccuracyCurve::operator==(const AccuracyCurve &other) const {
    return m_data == other.m_data;
}

bool AccuracyCurve::operator!=(const AccuracyCurve &other) const {
    return m_data != other.m_data;
}

[[maybe_unused]] QMap<int, QPair<double, double> > AccuracyCurve::getData() {
    return m_data;
}

void AccuracyCurve::passResultGraphics(GenericGraphicsView *receiver, const QString &fullFilePath) {
    auto *graphics = new QGraphicsSvgItem(fullFilePath);
    auto ptr = QSharedPointer<QGraphicsItem>(graphics);
    receiver->setAccuracyCurve(ptr);
}
