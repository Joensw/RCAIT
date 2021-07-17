#include <QThreadPool>
#include <utility>
#include <QGraphicsSvgItem>
#include <trainingresultview.h>
#include "abstractresultgraphics.h"

AbstractResultGraphics::AbstractResultGraphics(const QString &identifier, const QString &extension) {
    m_identifier = identifier;
    m_extension = extension;
    m_fullName = m_identifier + '.' + m_extension;
}

void AbstractResultGraphics::generateGraphics(TrainingResultView* receiver) {

    class GenerateGraphicsTask : public QRunnable {
    public:
        GenerateGraphicsTask(AbstractResultGraphics *abstract, QString fullFilePath, TrainingResultView* receiver) {
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
        TrainingResultView* m_receiver;
    };

    auto *generateGraphicsTask = new GenerateGraphicsTask(this, m_fullName, receiver);
    QThreadPool::globalInstance()->start(generateGraphicsTask);
}