#include "genericresultgraphics.h"

GenericResultGraphics::GenericResultGraphics(QString directory, QString baseName, QString extension)
        : m_baseName(std::move(baseName)),
          m_extension(std::move(extension)),
          m_directory(std::move(directory)) {
}

void GenericResultGraphics::generateGraphics(GenericGraphicsView *receiver) {
    auto generateGraphicsTask = QtConcurrent::run([this, receiver] {
        this->generateGraphicsInternal('"' % getFullPath() % '"');
        this->storeGraphicsFile(getFullPath(), getFullName());
        this->passResultGraphics(receiver, getFullPath());
        emit sig_graphicsGenerated(receiver, QSharedPointer<GenericResultGraphics>(this));
    });
    Q_UNUSED(generateGraphicsTask)
}

void GenericResultGraphics::storeGraphicsFile(const QString &tempFilePath, const QString &fileName) const {
    qDebug() << "Current path is : " << tempFilePath;
    qDebug() << "Results Dir is : " << ProjectManager::getInstance().getResultsDir();
    auto targetFilePath = ProjectManager::getInstance().getResultsDir() % "/" % fileName;
    QFile::copy(tempFilePath, targetFilePath);
    qDebug() << "File exists?" << QFileInfo::exists(targetFilePath);
}

[[maybe_unused]] const QString &GenericResultGraphics::getBaseName() const {
    return m_baseName;
}

[[maybe_unused]] const QString &GenericResultGraphics::getExtension() const {
    return m_extension;
}


[[maybe_unused]] const QString &GenericResultGraphics::getDirectory() const {
    return m_directory;
}

[[maybe_unused]] QString GenericResultGraphics::getFullName() const {
    return m_baseName % '.' % m_extension;
}

[[maybe_unused]] QString GenericResultGraphics::getFullPath() const {
    return m_directory % '/' % m_baseName % '.' % m_extension;
}

void GenericResultGraphics::launch_externalGraphicsGenerator(const QString &command, const QStringList &args) {
    auto commandWithArgs = QString("\"%1\" %2").arg(command, args.join(" "));

    QProcess process;
    process.startCommand(commandWithArgs);
    process.waitForStarted();
    process.waitForFinished();

    qInfo() << qPrintable("::::::" % commandWithArgs % "::::::") << "\n"
            << qPrintable(process.readAllStandardError().simplified()) << "\n"  //Print in console
            << qPrintable(process.readAll().simplified()) << "\n"               //Print in console
            << qPrintable("::::::" % QString("END OF OUTPUT") % "::::::") << "\n";

    process.close();
}
