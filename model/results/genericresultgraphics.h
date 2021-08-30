#ifndef ABSTRACTRESULTGRAPHICS_H
#define ABSTRACTRESULTGRAPHICS_H


#include <QString>
#include <QGraphicsView>
#include <utility>
#include <QGraphicsSvgItem>
#include <trainingresultview.h>
#include <QProcess>
#include <QtConcurrent/QtConcurrentRun>
#include <QStringBuilder>

class GenericResultGraphics {

private:
    const QString m_baseName;
    const QString m_extension;
    const QString m_fullName;
    const QString m_directory;
    const QString m_fullPath;

    virtual void generateGraphicsInternal(const QString &fullFilePath) = 0;

    virtual void passResultGraphics(const QString &fullFilePath, GenericGraphicsView *receiver) = 0;

public:
    GenericResultGraphics(const QString& directory, QString baseName, QString extension);

    void generateGraphics(GenericGraphicsView *receiver);

    [[nodiscard]] const QString &getBaseName() const;

    [[nodiscard]] const QString &getFullName() const;

    [[nodiscard]] const QString &getExtension() const;

    [[nodiscard]] const QString &getDirectory() const;

    [[nodiscard]] const QString &getFullPath() const;

protected:
    static void launch_externalGraphicsGenerator(const QString &command, const QStringList &args);

};

#endif // ABSTRACTRESULTGRAPHICS_H
