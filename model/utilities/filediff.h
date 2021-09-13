#ifndef FILEDIFF_H
#define FILEDIFF_H

#include <QObject>
#include <QPlainTextEdit>
#include <QFileInfo>
#include <QProcess>
#include <json_toolbox.h>
#include <codeeditor.h>
#include "ce_string.h"


class FileDiff : public QObject {
Q_OBJECT

public:
    FileDiff(const QSharedPointer<CodeEditor> &left, const QSharedPointer<CodeEditor> &right);

    void diff(const QString &file1, const QString &file2);

private:
    static constexpr CE_String HIGHLIGHTED_TEXT_TEMPLATE = "<span style=\"background-color:%1\">%2</span>";
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

    void sig_diffFinished(qsizetype longestLine);
};

#endif // FILEDIFF_H
