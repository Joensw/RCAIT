#include <QThreadPool>
#include <utility>
#include <QGraphicsSvgItem>
#include <trainingresultview.h>
#include <QProcess>
#include "abstractresultgraphics.h"

AbstractResultGraphics::AbstractResultGraphics(const QString &identifier, const QString &extension)
        : m_identifier(identifier),
          m_extension(extension),
          m_fullName(m_identifier + '.' + m_extension) {

}

void AbstractResultGraphics::generateGraphics(AbstractGraphicsView *receiver) {

    class GenerateGraphicsTask : public QRunnable {
    public:
        GenerateGraphicsTask(AbstractResultGraphics *abstract, QString fullFilePath, AbstractGraphicsView *receiver) {
            m_abstractResultGraphics = abstract;
            m_fullFilePath = std::move(fullFilePath);
            m_receiver = receiver;
        }

        void run() override {
            m_abstractResultGraphics->generateGraphicsInternal(m_fullFilePath);
            m_abstractResultGraphics->passResultGraphics(m_fullFilePath, m_receiver);
        }

    private:
        AbstractResultGraphics *m_abstractResultGraphics;
        QString m_fullFilePath;
        AbstractGraphicsView *m_receiver;
    };

    auto *generateGraphicsTask = new GenerateGraphicsTask(this, m_fullName, receiver);
    QThreadPool::globalInstance()->start(generateGraphicsTask);
}

QString AbstractResultGraphics::getIdentifier()
{
    return m_identifier;
}


void AbstractResultGraphics::launch_externalGraphicsGenerator(const QString &command, const QStringList &args) {
    auto *process = new QProcess();

    process->start(command, args);
    process->waitForStarted();
    process->waitForFinished();

    QString strTemp = QString::fromLocal8Bit(process->readAll());  // Get the output

    qInfo() << qPrintable(QString("===%1 %2===\n").arg(command,args.join(" ")))
            << qPrintable(strTemp.simplified()) << "\n" //Print in console
            << qPrintable(QString("===%1===").arg("END OF OUTPUT"));

    process->close();
}
