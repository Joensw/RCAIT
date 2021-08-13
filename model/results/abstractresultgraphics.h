#ifndef ABSTRACTRESULTGRAPHICS_H
#define ABSTRACTRESULTGRAPHICS_H


#include <QString>
#include <QGraphicsView>
#include <QThread>
#include <QRunnable>

class AbstractResultGraphics {

private:
    const QString m_baseName;
    const QString m_extension;
    const QString m_fullName;

    virtual void generateGraphicsInternal(const QString &fullFilePath) = 0;

    virtual void passResultGraphics(const QString &fullFilePath, AbstractGraphicsView *receiver) = 0;

public:
    AbstractResultGraphics(QString baseName, QString extension);

    void generateGraphics(AbstractGraphicsView *receiver);

    [[nodiscard]] const QString &getBaseName() const;

    [[nodiscard]] const QString &getFullName() const;

    [[nodiscard]] const QString &getExtension() const;

protected:
    static void launch_externalGraphicsGenerator(const QString &command, const QStringList &args);

};

#endif // ABSTRACTRESULTGRAPHICS_H
