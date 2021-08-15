#include <QThreadPool>
#include <utility>
#include <QGraphicsSvgItem>
#include <trainingresultview.h>
#include <QProcess>
#include <QtConcurrent/QtConcurrentRun>
#include "abstractresultgraphics.h"

AbstractResultGraphics::AbstractResultGraphics(const QString& directory, QString baseName, QString extension)
        : m_baseName(std::move(baseName)),
          m_extension(std::move(extension)),
          m_fullName(m_baseName + '.' + m_extension),
          m_directory(directory),
          m_fullPath(directory + '/' + m_fullName){

}

void AbstractResultGraphics::generateGraphics(AbstractGraphicsView *receiver) {
    auto generateGraphicsTask = QtConcurrent::run([this,receiver] {
        this->generateGraphicsInternal(m_fullPath);
        this->passResultGraphics(m_fullPath, receiver);
    });
    Q_UNUSED(generateGraphicsTask)
}

const QString &AbstractResultGraphics::getBaseName() const {
    return m_baseName;
}

const QString &AbstractResultGraphics::getExtension() const {
    return m_extension;
}

const QString &AbstractResultGraphics::getFullName() const {
    return m_fullName;
}

const QString &AbstractResultGraphics::getDirectory() const {
    return m_directory;
}

const QString &AbstractResultGraphics::getFullPath() const {
    return m_fullPath;
}

void AbstractResultGraphics::launch_externalGraphicsGenerator(const QString &command, const QStringList &args) {
    auto *process = new QProcess();

    process->start(command, args);
    process->waitForStarted();
    process->waitForFinished();

    QString strTemp = QString::fromLocal8Bit(process->readAll());  // Get the output

    qInfo() << qPrintable(QString("===%1 %2===\n").arg(command, args.join(" ")))
            << qPrintable(strTemp.simplified()) << "\n" //Print in console
            << qPrintable(QString("===%1===").arg("END OF OUTPUT"));

    process->close();
}
