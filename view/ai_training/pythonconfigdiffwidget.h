#ifndef PYTHONCONFIGDIFFWIDGET_H
#define PYTHONCONFIGDIFFWIDGET_H

#include <QWidget>
#include <QPlainTextEdit>
#include <QFileDialog>
#include <QFile>

namespace Ui {
    class PythonConfigDiffWidget;
}

class PythonConfigDiffWidget : public QWidget {
Q_OBJECT

public:
    explicit PythonConfigDiffWidget(QWidget *parent = nullptr);

    ~PythonConfigDiffWidget() override;

private slots:

    void on_pushButton_loadLeftFile_clicked();

    void on_pushButton_loadRightFile_clicked();

    void on_pushButton_startDiff_clicked();

private:
    static constexpr auto FONT_NAME = "Inter Monospace";
    static constexpr auto FONT_SIZE = 8;

    Ui::PythonConfigDiffWidget *ui;
    QString m_leftFilePath;
    QString m_rightFilePath;

    QString openFile(QPlainTextEdit *);
};

#endif // PYTHONCONFIGDIFFWIDGET_H
