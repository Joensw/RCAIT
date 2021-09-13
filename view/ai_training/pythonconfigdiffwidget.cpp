#include "pythonconfigdiffwidget.h"
#include <QScrollBar>
#include "ui_pythonconfigdiffwidget.h"

PythonConfigDiffWidget::PythonConfigDiffWidget(QWidget *parent) :
        QWidget(parent),
        ui(new Ui::PythonConfigDiffWidget) {
    ui->setupUi(this);

    m_leftCodeEditor.reset(ui->codeEditor_left, &QObject::deleteLater);
    m_rightCodeEditor.reset(ui->codeEditor_right, &QObject::deleteLater);
    m_fileDiff.reset(new FileDiff(m_leftCodeEditor, m_rightCodeEditor));

    connect(&*m_fileDiff, &FileDiff::sig_diffFinished, this, &PythonConfigDiffWidget::slot_diffFinished);

    auto v_leftScrollBar = m_leftCodeEditor->verticalScrollBar();
    auto h_leftScrollBar = m_leftCodeEditor->horizontalScrollBar();
    auto v_rightScrollBar = m_rightCodeEditor->verticalScrollBar();
    auto h_rightScrollBar = m_rightCodeEditor->horizontalScrollBar();

    connect(v_leftScrollBar, &QScrollBar::valueChanged, v_rightScrollBar, &QScrollBar::setValue);
    connect(v_rightScrollBar, &QScrollBar::valueChanged, v_leftScrollBar, &QScrollBar::setValue);
    connect(h_leftScrollBar, &QScrollBar::valueChanged, h_rightScrollBar, &QScrollBar::setValue);
    connect(h_rightScrollBar, &QScrollBar::valueChanged, h_leftScrollBar, &QScrollBar::setValue);

    QFont font(FONT_NAME, FONT_SIZE);
    ui->codeEditor_left->setFont(font);
    ui->codeEditor_right->setFont(font);
}

PythonConfigDiffWidget::~PythonConfigDiffWidget() {
    delete ui;
}


[[maybe_unused]] void PythonConfigDiffWidget::on_pushButton_loadLeftFile_clicked() {
    auto fileName = openFile(ui->codeEditor_left);
    if (!fileName.isEmpty()) {
        m_leftFilePath = fileName;
        ui->groupBox_leftFile->setTitle(m_leftFilePath);
    }
}


[[maybe_unused]] void PythonConfigDiffWidget::on_pushButton_loadRightFile_clicked() {
    auto fileName = openFile(ui->codeEditor_right);
    if (!fileName.isEmpty()) {
        m_rightFilePath = fileName;
        ui->groupBox_rightFile->setTitle(m_rightFilePath);
    }
}


[[maybe_unused]] void PythonConfigDiffWidget::on_pushButton_startDiff_clicked() {
    m_leftCodeEditor->reset();
    m_rightCodeEditor->reset();
    m_fileDiff->diff(m_leftFilePath, m_rightFilePath);
}

void PythonConfigDiffWidget::slot_diffFinished(qsizetype longestLine) {
    QString placeholder;
    placeholder.fill(' ', longestLine);
    m_leftCodeEditor->appendPlaceholder(placeholder);
    m_rightCodeEditor->appendPlaceholder(placeholder);

    //Scroll to first line
    m_leftCodeEditor->moveCursor(QTextCursor::Start);
    m_rightCodeEditor->moveCursor(QTextCursor::Start);
    m_leftCodeEditor->ensureCursorVisible();
    m_rightCodeEditor->ensureCursorVisible();
}

QString PythonConfigDiffWidget::openFile(CodeEditor *codeView) {
    Q_ASSERT(codeView);

    auto fileName = QFileDialog::getOpenFileName(this, tr("Open File"),
                                                 "", "Python Files (*.py)");

    if (fileName.isEmpty()) return {};

    QFile file(fileName);
    if (file.open(QFile::ReadOnly | QFile::Text)) {
        codeView->reset();
        codeView->setPlainText(file.readAll());
        return fileName;
    }
    return {};
}

