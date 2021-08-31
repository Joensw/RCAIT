#include "genericresultgraphics.h"

GenericResultGraphics::GenericResultGraphics(const QString &directory, QString baseName, QString extension)
        : m_baseName(std::move(baseName)),
          m_extension(std::move(extension)),
          m_fullName(m_baseName % '.' % m_extension),
          m_directory(directory),
          m_fullPath(directory % m_fullName) {

}

void GenericResultGraphics::generateGraphics(GenericGraphicsView *receiver) {
    auto generateGraphicsTask = QtConcurrent::run([this, receiver] {
        this->generateGraphicsInternal('"' % m_fullPath % '"');
        this->passResultGraphics(m_fullPath, receiver);
    });
    Q_UNUSED(generateGraphicsTask)
}

const QString &GenericResultGraphics::getBaseName() const {
    return m_baseName;
}

const QString &GenericResultGraphics::getExtension() const {
    return m_extension;
}

const QString &GenericResultGraphics::getFullName() const {
    return m_fullName;
}

const QString &GenericResultGraphics::getDirectory() const {
    return m_directory;
}

const QString &GenericResultGraphics::getFullPath() const {
    return m_fullPath;
}

void GenericResultGraphics::launch_externalGraphicsGenerator(const QString &command, const QStringList &args) {
    auto commandWithArgs = command + " " + args.join(" ");

    QProcess process;
    process.startCommand(commandWithArgs);
    process.waitForStarted();
    process.waitForFinished();

    qInfo() << qPrintable("::::::" % commandWithArgs % "::::::" % "\n")
            << qPrintable(process.readAllStandardError().simplified().append("\n")) //Print in console
            << qPrintable(process.readAll().simplified().append("\n")) //Print in console
            << qPrintable("::::::" % QString("END OF OUTPUT") % "::::::" % "\n");

    process.close();
}
