#include "classificationgraphics.h"

ClassificationGraphics::ClassificationGraphics(const QString &directory, const QString &identifier,
                                               const QMap<QString, QList<double>> &data,
                                               const QStringList &classLabels)
        : GenericResultGraphics(directory, "classification_" % identifier, "svg"),
          m_data(data),
          m_classLabels(classLabels) {

}

QString ClassificationGraphics::dataToPyText() {
    QStringList result;

    for (const auto &row_data: qAsConst(m_data)) {
        //List for each row, which shall be joined in a single QString
        QStringList rowList;

        //Convert to QString with precision of 2 digits
        for (const auto &value: row_data) {
            auto valueStr = QString::number(value, 'f', 2);
            rowList << valueStr;
        }
        result << '[' % rowList.join(',') % ']';
    }
    return '[' % result.join(',') % ']';
}

QString ClassificationGraphics::imagePathsToPyText() {
    QStringList results;
    for (const auto&[imagePath, _]: MapAdapt(m_data)) {
        results << "'" % imagePath % "'";
    }
    //Add "" around string so that dashes are not recognized as new arguments
    return '"' % ('[' % results.join(',') % ']') % '"';
}

QString ClassificationGraphics::classLabelsToPyText() {
    QStringList results;
    for (const auto &class_label: m_classLabels) {
        results << "'" % class_label % "'";
    }
    //Add "" around string so that dashes are not recognized as new arguments
    return '"' % ('[' % results.join(',') % ']') % '"';
}

[[maybe_unused]] void ClassificationGraphics::addClassificationEntry(const QString &identifier, const QList<double> &data) {
    m_data.insert(identifier, data);
}

[[maybe_unused]] void ClassificationGraphics::removeClassificationEntry(const QString &identifier) {
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
    auto params = {pyScript.absoluteFilePath(), dataToPyText(), imagePathsToPyText(), classLabelsToPyText(),
                   fullFilePath};
    auto command = ConfigurationManager::getInstance().getPythonExecutablePath();
    GenericResultGraphics::launch_externalGraphicsGenerator(command, params);
}

void ClassificationGraphics::passResultGraphics(GenericGraphicsView *receiver, const QString &fullFilePath) {
    auto *graphics = new QGraphicsSvgItem(fullFilePath);
    auto ptr = QSharedPointer<QGraphicsItem>(graphics);
    receiver->setClassificationGraphics(ptr);
}
