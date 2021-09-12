#include <QtConcurrent/QtConcurrent>
#include "filediff.h"

enum GraphicsType {
    SIMILAR = 0,         // line hasn't changed between the files, its diff starts with '  '
    RIGHTONLY = 1,       // line exists in the right file only, its diff starts with '+ '
    LEFTONLY = 2,        // line exists in the left file only, its diff starts with '- '
    CHANGED = 3,         // line has incremental changes on the left file, the diff is represented
};

FileDiff::FileDiff(const QSharedPointer<QPlainTextEdit> &left, const QSharedPointer<QPlainTextEdit> &right)
        : m_leftTextEdit(left),
          m_rightTextEdit(right) {
}

QString FileDiff::color(const QString &text, QColor color) {
    auto hex = color.name();
    return QString("<span style=\"background-color:%1\">%2</span>").arg(hex, text);
}

void FileDiff::slot_parseLine() {
    while (m_process->canReadLine()) {
        auto jsonObject = JSON_Toolbox::readJSON(m_process->readLine());

        auto json_leftchanges = jsonObject["leftchanges"].toArray();
        auto json_rightchanges = jsonObject["rightchanges"].toArray();

        int code = jsonObject["code"].toInt();
        auto line = jsonObject["line"].toString();
        auto newline = jsonObject["newline"].toString();
        auto leftchanges = QJsonArray_toList<int>(json_leftchanges);
        auto rightchanges = QJsonArray_toList<int>(json_rightchanges);

        QString tempLeft, tempRight;
        switch (code) {
            case SIMILAR:
                m_leftTextEdit->appendHtml(line);
                m_rightTextEdit->appendHtml(line);
                break;
            case RIGHTONLY:
                m_leftTextEdit->appendHtml(color("\n", GREY)); //gray
                m_rightTextEdit->appendHtml(color(line, GREEN)); //green
                break;
            case LEFTONLY:
                m_leftTextEdit->appendHtml(color(line, RED)); //red
                m_rightTextEdit->appendHtml(color("\n", GREY)); //gray
                break;
            case CHANGED:
                tempLeft.reserve(color(line, RED).length());
                for (int i = 0; i < line.length(); i++) {
                    auto letter = line[i];
                    QColor tone = (leftchanges.contains(i)) ? DARKRED : RED;
                    tempLeft.append(color(letter, tone)); //darkred if i in leftchanges else red
                }
                tempRight.reserve(color(newline, GREEN).length());
                for (int i = 0; i < newline.length(); i++) {
                    auto letter = newline[i];
                    QColor tone = (rightchanges.contains(i)) ? DARKGREEN : GREEN;
                    tempRight.append(color(letter, tone)); //darkgreen if i in rightchanges else green
                }
                m_leftTextEdit->appendHtml(tempLeft);
                m_rightTextEdit->appendHtml(tempRight);
                break;
            default:
                qDebug() << "Unknown code received. Ignoring.";
                break;
        }
    }
}

void FileDiff::diff(const QString &file1, const QString &file2) {
    auto pythonScript = QFileInfo("filediff.py");
    auto command = "python";
    auto args = {pythonScript.absoluteFilePath(), file1, file2};

    m_process.reset(new QProcess);

    connect(&*m_process, &QProcess::readyReadStandardOutput, this, &FileDiff::slot_parseLine);
    m_process->setReadChannel(QProcess::StandardOutput);

    m_process->start(command, args);
}