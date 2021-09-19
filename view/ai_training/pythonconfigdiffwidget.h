#ifndef PYTHONCONFIGDIFFWIDGET_H
#define PYTHONCONFIGDIFFWIDGET_H

#include <QWidget>
#include <QPlainTextEdit>
#include <QFileDialog>
#include <QFile>
#include <filediff.h>
#include <QGroupBox>
#include "codeeditor.h"

namespace Ui {
    class PythonConfigDiffWidget;
}

/**
 * @brief This widget is used to compare ("diff") two config files in <code>.py</code> format,
 * used to configure model parameters.
 */
class PythonConfigDiffWidget : public QWidget {
Q_OBJECT

protected:

    /**
     * @brief changeEvent event handler
     * @param event incoming event
     */
    void changeEvent(QEvent *event) override;

public:
    /**
     * @brief Constructs a PythonConfigDiffWidget
     * @param parent parent widget (optional)
     */
    explicit PythonConfigDiffWidget(QWidget *parent = nullptr);

    /**
     * @brief Destructor of this class.
     */
    ~PythonConfigDiffWidget() override;

private slots:

    [[maybe_unused]] void on_pushButton_loadLeftFile_clicked();

    [[maybe_unused]] void on_pushButton_loadRightFile_clicked();

    [[maybe_unused]] void on_pushButton_startDiff_clicked();

    void slot_diffFinished(qsizetype longestLine);

private:
    static constexpr auto FONT_NAME = "Inter Monospace";
    static constexpr auto FONT_SIZE = 8;

    Ui::PythonConfigDiffWidget *ui;
    QSharedPointer<CodeEditor> m_leftCodeEditor, m_rightCodeEditor;
    QScopedPointer<FileDiff> m_fileDiff;
    QString m_leftFilePath;
    QString m_rightFilePath;

    bool openFile(QString& fileName);

    static bool openFileHelper(CodeEditor *codeView, QGroupBox *box,const QString &fileName);

    void loadFileHelper(QString &fileName);
};

#endif // PYTHONCONFIGDIFFWIDGET_H
