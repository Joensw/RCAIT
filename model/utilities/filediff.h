#ifndef FILEDIFF_H
#define FILEDIFF_H

#include <QObject>
#include <QPlainTextEdit>
#include <QFileInfo>
#include <QProcess>
#include <json_toolbox.h>
#include <codeeditor.h>
#include "ce_string.h"
#include <configurationmanager.h>
#include <QtConcurrent/QtConcurrent>


/**
 * @brief This class can create a diff of two files. It makes use of pythons <code>difflib</code>.
 * The diff code is formatted and inserted as <code>HTML</code> into a supported CodeEditor widget.
 */
class FileDiff : public QObject {
Q_OBJECT

public:
    /**
     * @brief Constructs a FileDiff object.
     * @param left shared pointer to a CodeEditor to display diff data to the left
     * @param right shared pointer to a CodeEditor to display diff data to the right
     */
    FileDiff(const QSharedPointer<CodeEditor> &left, const QSharedPointer<CodeEditor> &right);

    /**
     * @brief Launches diff creation by making use of pythons <code>difflib</code>
     * @param file1 first file to compare
     * @param file2 second file to compare to
     */
    void diff(const QString &file1, const QString &file2);

private:
    static constexpr CE_String HIGHLIGHTED_TEXT_TEMPLATE = "<span style=\"background-color:%1\">%2</span>";
    //Calculated String length when %1 is filled with a Hex Code and %2 with a char (length = 1)
    //This String length will always be the same and can be reserved to prevent an allocation of more space
    static constexpr auto HIGHLIGHTED_TEXT_TEMPLATE_LENGTH = HIGHLIGHTED_TEXT_TEMPLATE.size() + 4;

    static constexpr QColor GREEN = QColorConstants::Svg::palegreen;
    static constexpr QColor DARKGREEN = QColorConstants::Svg::limegreen;
    static constexpr QColor RED = QColorConstants::Svg::palevioletred;
    static constexpr QColor DARKRED = QColorConstants::Svg::firebrick;

    QSharedPointer<CodeEditor> m_leftCodeEditor, m_rightCodeEditor;
    QScopedPointer<QProcess> m_process;
    qsizetype m_maxLineWidth;

    static QString color(const QString &text, QColor color);

private slots:

    void slot_parseLine();

    void slot_processFinished(int exitCode, QProcess::ExitStatus exitStatus);

signals:

    /**
     * @brief This signal is emitted when the diff creation has finished.
     * @param longestLine longest line encountered when creating the diff.
     */
    void sig_diffFinished(qsizetype longestLine);
};

#endif // FILEDIFF_H
