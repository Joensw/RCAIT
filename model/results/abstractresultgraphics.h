#ifndef ABSTRACTRESULTGRAPHICS_H
#define ABSTRACTRESULTGRAPHICS_H


#include <QString>
#include <QGraphicsView>
#include <QThread>
#include <QRunnable>

class AbstractResultGraphics {

private:
    QString m_identifier;
    QString m_extension;
    QString m_fullName;

    virtual void generateGraphicsInternal(const QString &fullFilePath) = 0;

    virtual void passResultGraphics(const QString &fullFilePath, TrainingResultView* receiver) = 0;

public:
    AbstractResultGraphics(const QString &identifier, const QString &extension);

    void generateGraphics(TrainingResultView* receiver);

};

#endif // ABSTRACTRESULTGRAPHICS_H
