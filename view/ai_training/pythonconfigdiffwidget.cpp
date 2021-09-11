#include "pythonconfigdiffwidget.h"
#include "ui_pythonconfigdiffwidget.h"

PythonConfigDiffWidget::PythonConfigDiffWidget(QWidget *parent) :
        QWidget(parent),
        ui(new Ui::PythonConfigDiffWidget) {
    ui->setupUi(this);

    QFont font(FONT_NAME, FONT_SIZE);
    ui->codeEditor_left->setFont(font);
    ui->codeEditor_right->setFont(font);
}

PythonConfigDiffWidget::~PythonConfigDiffWidget() {
    delete ui;
}


void PythonConfigDiffWidget::on_pushButton_loadLeftFile_clicked() {
    auto fileName = openFile(ui->codeEditor_left);
    if (!fileName.isEmpty()) {
        m_leftFilePath = fileName;
        ui->groupBox_leftFile->setTitle(m_leftFilePath);
    }
}


void PythonConfigDiffWidget::on_pushButton_loadRightFile_clicked() {
    auto fileName = openFile(ui->codeEditor_right);
    if (!fileName.isEmpty()) {
        m_rightFilePath = fileName;
        ui->groupBox_rightFile->setTitle(m_rightFilePath);
    }
}


void PythonConfigDiffWidget::on_pushButton_startDiff_clicked() {
}

QString PythonConfigDiffWidget::openFile(QPlainTextEdit *codeView) {
    Q_ASSERT(codeView);

    auto fileName = QFileDialog::getOpenFileName(this, tr("Open File"),
                                                 "", "Python Files (*.py)");

    if (fileName.isEmpty()) return {};

    QFile file(fileName);
    if (file.open(QFile::ReadOnly | QFile::Text)) {
        codeView->setPlainText(file.readAll());
        return fileName;
    }
    return {};
}

