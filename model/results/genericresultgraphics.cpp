#include <QThreadPool>
#include <utility>
#include <QGraphicsSvgItem>
#include <trainingresultview.h>
#include <QProcess>
#include <QtConcurrent/QtConcurrentRun>
#include "genericresultgraphics.h"

GenericResultGraphics::GenericResultGraphics(const QString &directory, QString baseName, QString extension)
        : m_baseName(std::move(baseName)),
          m_extension(std::move(extension)),
          m_fullName(m_baseName + '.' + m_extension),
          m_directory(directory),
          m_fullPath(directory + m_fullName) {

}

void GenericResultGraphics::generateGraphics(GenericGraphicsView *receiver) {
    auto generateGraphicsTask = QtConcurrent::run([this, receiver] {
        this->generateGraphicsInternal('"' + m_fullPath + '"');
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
    auto *process = new QProcess();
    auto commandWithArgs = command + " " + args.join(" ");
    process->startCommand(commandWithArgs);
    process->waitForStarted();
    process->waitForFinished();

    QString strTemp = QString::fromLocal8Bit(process->readAll());  // Get the output

    qInfo() << QString("===%1===\n").arg(commandWithArgs)
            << QString("%1\n").arg(strTemp.simplified()) //Print in console
            << QString("===%1===\n").arg("END OF OUTPUT");

    process->close();
}
