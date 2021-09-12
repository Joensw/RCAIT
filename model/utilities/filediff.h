#ifndef FILEDIFF_H
#define FILEDIFF_H

#include <QObject>
#include <QPlainTextEdit>
#include <QFileInfo>
#include <QProcess>
#include <json_toolbox.h>


class FileDiff : public QObject {
Q_OBJECT

public:
    FileDiff(const QSharedPointer<QPlainTextEdit> &left, const QSharedPointer<QPlainTextEdit> &right);

    void diff(const QString &file1, const QString &file2);

private:
    static constexpr QColor GREEN = QColorConstants::Svg::palegreen;
    static constexpr QColor DARKGREEN = QColorConstants::Svg::limegreen;
    static constexpr QColor RED = QColorConstants::Svg::palevioletred;
    static constexpr QColor DARKRED = QColorConstants::Svg::firebrick;
    static constexpr QColor GREY = QColorConstants::Svg::lightsteelblue;

    QSharedPointer<QPlainTextEdit> m_leftTextEdit, m_rightTextEdit;
    QScopedPointer<QProcess> m_process;

    static QString color(const QString &text, QColor color);

private slots:

    void slot_parseLine();
};

#endif // FILEDIFF_H
