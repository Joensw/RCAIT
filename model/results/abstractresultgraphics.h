#ifndef ABSTRACTRESULTGRAPHICS_H
#define ABSTRACTRESULTGRAPHICS_H


#include <QString>
#include <QGraphicsView>
#include <QThread>
#include <QRunnable>

class AbstractResultGraphics {

private:
    const QString m_identifier;
    const QString m_extension;
    const QString m_fullName;

    virtual void generateGraphicsInternal(const QString &fullFilePath) = 0;

    virtual void passResultGraphics(const QString &fullFilePath, AbstractGraphicsView *receiver) = 0;

public:
    AbstractResultGraphics(const QString &identifier, const QString &extension);

    void generateGraphics(AbstractGraphicsView *receiver);

protected:
    static void launch_externalGraphicsGenerator(const QString &command, const QStringList &args);

};

#endif // ABSTRACTRESULTGRAPHICS_H
