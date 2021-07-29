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

    virtual void passResultGraphics(const QString &fullFilePath, AbstractGraphicsView *receiver) = 0;

public:
    AbstractResultGraphics(QString identifier, QString extension);

    void generateGraphics(AbstractGraphicsView *receiver);

    QString getIdentifier();

    void updateIdentifier(const QString &identifier);

    void updateExtension(const QString &extension);

protected:
    static void launch_externalGraphicsGenerator(const QString &command, const QStringList &args);

};

#endif // ABSTRACTRESULTGRAPHICS_H
