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
    loadFileHelper(m_leftFilePath);
}

[[maybe_unused]] void PythonConfigDiffWidget::on_pushButton_loadRightFile_clicked() {
    loadFileHelper(m_rightFilePath);
}


[[maybe_unused]] void PythonConfigDiffWidget::on_pushButton_startDiff_clicked() {
    m_leftCodeEditor->reset();
    m_rightCodeEditor->reset();
    m_fileDiff->diff(m_leftFilePath, m_rightFilePath);
    ui->pushButton_startDiff->setEnabled(false);
}

void PythonConfigDiffWidget::slot_diffFinished(qsizetype longestLine) {
    //Add a line with spaces as long as the longest line encountered in both files.
    //This ensures that horizontal scrollbars are synchronized.
    QString placeholder;
    placeholder.fill(' ', longestLine);
    m_leftCodeEditor->appendPlaceholder(placeholder);
    m_rightCodeEditor->appendPlaceholder(placeholder);

    //Scroll up to first line
    m_leftCodeEditor->moveCursor(QTextCursor::Start);
    m_rightCodeEditor->moveCursor(QTextCursor::Start);
    m_leftCodeEditor->ensureCursorVisible();
    m_rightCodeEditor->ensureCursorVisible();
}

bool PythonConfigDiffWidget::openFile(QString &fileName) {

    auto openedFile = QFileDialog::getOpenFileName(this, tr("Open File"),
                                                   "", tr("Python Files (*.py)"));

    if (openedFile.isEmpty()) return false;
    fileName = openedFile;
    return true;
}

bool PythonConfigDiffWidget::openFileHelper(CodeEditor *codeView, QGroupBox *box, const QString &fileName) {
    if (fileName.isEmpty()) return false;

    QFile file(fileName);
    if (file.open(QFile::ReadOnly | QFile::Text)) {
        codeView->reset();
        //Check if diff view was reset including leftover html colours
        Q_ASSERT(codeView->document()->isEmpty());
        codeView->setPlainText(file.readAll());
        box->setTitle(fileName);
        return true;
    }
    return false;
}

void PythonConfigDiffWidget::loadFileHelper(QString &fileName) {
    if (openFile(fileName)) {
        ui->pushButton_startDiff->setEnabled(!m_leftFilePath.isEmpty() && !m_rightFilePath.isEmpty());
        openFileHelper(ui->codeEditor_left, ui->groupBox_leftFile, m_leftFilePath);
        openFileHelper(ui->codeEditor_right, ui->groupBox_rightFile, m_rightFilePath);
    }
}

void PythonConfigDiffWidget::changeEvent(QEvent *event) {
    if (event->type() == QEvent::LanguageChange) {
        // this event is sent if a translator is loaded
        ui->retranslateUi(this);
    }
    //Call to parent class
    QWidget::changeEvent(event);
}

