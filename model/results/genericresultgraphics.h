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

/**
 * @brief Superclass of all specialised result graphics.
 * This class contains common code and methods required by all specialised result graphics.
 */
class GenericResultGraphics : public QObject {
Q_OBJECT

private:
    const QString m_baseName;
    const QString m_extension;
    const QString m_directory;

    /**
     * @brief Internal generation method. Used to visualise specialised result graphics.
     * The exact implementation is left to the subclass.
     * @param fullFilePath output file path of the result graphics
     */
    virtual void generateGraphicsInternal(const QString &fullFilePath) = 0;

    /**
     * @brief Passes the generated graphics to a result view.
     * @param receiver result view to display the generated graphics
     * @param fullFilePath path to generated graphics file
     */
    virtual void passResultGraphics(GenericGraphicsView *receiver, const QString &fullFilePath) = 0;

public:
    /**
     * @brief Constructs GenericResultGraphics
     * @param directory Saving directory for result
     * @param baseName Name of the output file without extension
     * @param extension extension of the file
     */
    GenericResultGraphics(QString directory, QString baseName, QString extension);

    /**
     * @brief Launch generation process of output file.
     * Uses a different thread to launch the process.
     * The exact implementation of the generation is left to the subclass.
     * @param receiver result view to display the generated graphics
     */
    void generateGraphics(GenericGraphicsView *receiver);

    /**
     * @brief Get the output file base name
     * @return base name without extension
     */
    [[maybe_unused]] [[nodiscard]] const QString &getBaseName() const;

    /**
     * @brief Get the full name of the output file
     * @return full file name
     */
    [[maybe_unused]] [[nodiscard]] QString getFullName() const;

    /**
     * @brief Get the extension of the output file
     * @return file extension
     */
    [[maybe_unused]] [[nodiscard]] const QString &getExtension() const;

    /**
     * @brief Get the directory of the output file
     * @return output directory
     */
    [[maybe_unused]] [[nodiscard]] const QString &getDirectory() const;

    /**
     * @brief Get the full file path of the output file (consists of directory and full file name)
     * @return full file path
     */
    [[maybe_unused]] [[nodiscard]] QString getFullPath() const;

signals:

    /**
     * @brief Emitted when graphics generation finished
     * @param receiver result view to display the generated graphics
     * @param graphics graphics object that was visualized
     */
    void sig_graphicsGenerated(GenericGraphicsView *receiver, QSharedPointer<GenericResultGraphics> graphics);

protected:
    /**
     * @brief Helper method to launch an external graphics generation command.
     * This methods takes care of spawning a process and redirecting console outputs.
     * @param command command to execute
     * @param args list of command arguments
     */
    static void launch_externalGraphicsGenerator(const QString &command, const QStringList &args);

};

#endif // ABSTRACTRESULTGRAPHICS_H
