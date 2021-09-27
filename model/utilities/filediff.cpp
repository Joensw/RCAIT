#include "filediff.h"

/**
 * @brief Every line in a diff gets a change code.
 * This enum contains these codes and their meanings.
 */
enum DiffCode {
    SIMILAR = 0,         /// line hasn't changed between the files, its diff starts with '  '
    RIGHTONLY = 1,       /// line exists in the right file only, its diff starts with '+ '
    LEFTONLY = 2,        /// line exists in the left file only, its diff starts with '- '
    CHANGED = 3,         /// line has incremental changes on the left file, the diff is represented
};

FileDiff::FileDiff(const QSharedPointer<CodeEditor> &left, const QSharedPointer<CodeEditor> &right)
        : m_leftCodeEditor(left),
          m_rightCodeEditor(right),
          m_maxLineWidth(0) {
}

QString FileDiff::color(const QString &text, QColor color) {
    auto hex = color.name();
    return HIGHLIGHTED_TEXT_TEMPLATE.arg(hex, text);
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

        m_maxLineWidth = std::max({m_maxLineWidth, line.size(), newline.size()});
        QString tempLeft, tempRight;
        switch (code) {
            case SIMILAR:
                m_leftCodeEditor->appendHtml(line);
                m_rightCodeEditor->appendHtml(line);
                break;
            case RIGHTONLY:
                m_leftCodeEditor->appendPlaceholder();
                m_rightCodeEditor->appendHtml(color(line, GREEN));
                break;
            case LEFTONLY:
                m_leftCodeEditor->appendHtml(color(line, RED));
                m_rightCodeEditor->appendPlaceholder();
                break;
            case CHANGED:
                tempLeft.reserve(HIGHLIGHTED_TEXT_TEMPLATE_LENGTH * line.length());
                for (int i = 0; i < line.length(); i++) {
                    QColor tone = leftchanges.contains(i) ? DARKRED : RED;
                    tempLeft.append(color(line[i], tone));
                }

                tempRight.reserve(HIGHLIGHTED_TEXT_TEMPLATE_LENGTH * newline.length());
                for (int i = 0; i < newline.length(); i++) {
                    QColor tone = rightchanges.contains(i) ? DARKGREEN : GREEN;
                    tempRight.append(color(newline[i], tone));
                }

                m_leftCodeEditor->appendHtml(tempLeft);
                m_rightCodeEditor->appendHtml(tempRight);
                break;
            default:
                qDebug() << "Unknown code received. Ignoring.";
                break;
        }
    }
}

void FileDiff::slot_processFinished(int exitCode, QProcess::ExitStatus exitStatus) {
    if (exitCode == 0 && exitStatus == QProcess::NormalExit) {
        emit sig_diffFinished(m_maxLineWidth);
    }
}

void FileDiff::diff(const QString &file1, const QString &file2) {
    m_maxLineWidth = 0;
    auto pythonScript = QFileInfo("filediff.py");
    const auto MANAGER = ConfigurationManager::getInstance();
    auto command = MANAGER->getPythonExecutablePath();
    QStringList args = {pythonScript.absoluteFilePath(), file1, file2};

    m_process.reset(new QProcess);

    connect(&*m_process, &QProcess::readyReadStandardOutput, this, &FileDiff::slot_parseLine);
    connect(&*m_process, &QProcess::finished, this, &FileDiff::slot_processFinished);

    m_process->setReadChannel(QProcess::StandardOutput);

    qDebug() << command % " " % args.join(" ") % "\n";
    m_process->start(command, args);
}