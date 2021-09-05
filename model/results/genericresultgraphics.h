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

class GenericResultGraphics : public QObject {
Q_OBJECT

private:
    const QString m_baseName;
    const QString m_extension;
    const QString m_fullName;
    const QString m_directory;
    const QString m_fullPath;

    virtual void generateGraphicsInternal(const QString &fullFilePath) = 0;

    virtual void passResultGraphics(const QString &fullFilePath, GenericGraphicsView *receiver) = 0;

public:
    GenericResultGraphics(const QString &directory, QString baseName, QString extension);

    void generateGraphics(GenericGraphicsView *receiver);

    [[maybe_unused]] [[nodiscard]] const QString &getBaseName() const;

    [[maybe_unused]] [[nodiscard]] const QString &getFullName() const;

    [[maybe_unused]] [[nodiscard]] const QString &getExtension() const;

    [[maybe_unused]] [[nodiscard]] const QString &getDirectory() const;

    [[maybe_unused]] [[nodiscard]] const QString &getFullPath() const;

signals:

    void sig_graphicsGenerated(GenericGraphicsView *receiver, GenericResultGraphics *graphics, const QString &fullPath);

protected:
    static void launch_externalGraphicsGenerator(const QString &command, const QStringList &args);

};

#endif // ABSTRACTRESULTGRAPHICS_H
