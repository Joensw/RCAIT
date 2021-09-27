#include <gtest/gtest.h>
#include <QSignalSpy>
#include <qapplication.h>
#include <QDir>
#include <codeeditor.h>
#include <filediff.h>
#include <settingsmanager.h>


class FileDiffTests : public testing::Test {

protected:
    QDir dir;
    QString file_left, file_right;
    QString diff_left, diff_right;

    //copy test files to new directory
    void SetUp() override {
        qInstallMessageHandler(myMessageHandler);
        dir = QDir(QDir::current().path());
        EXPECT_TRUE(dir.exists());

        file_left = dir.absoluteFilePath("configs/MobilNetTest_main.py");
        diff_left = dir.absoluteFilePath("configs/MobilNetTest_main_diff_nocolor.txt");
        file_right = dir.absoluteFilePath("configs/res666_main.py");
        diff_right = dir.absoluteFilePath("configs/res666_main_diff_nocolor.txt");
        EXPECT_TRUE(QFile(file_left).exists());
        EXPECT_TRUE(QFile(file_right).exists());
        EXPECT_TRUE(QFile(diff_left).exists());
        EXPECT_TRUE(QFile(diff_right).exists());

        [[maybe_unused]] const auto MANAGER = &SettingsManager::getInstance();
    }

    static void myMessageHandler(QtMsgType type, const QMessageLogContext &, const QString &msg) {
        QString txt;
        switch (type) {
            case QtDebugMsg:
                txt = QString("Debug: %1").arg(msg);
                break;
            case QtWarningMsg:
                txt = QString("Warning: %1").arg(msg);
                break;
            case QtCriticalMsg:
                txt = QString("Critical: %1").arg(msg);
                break;
            case QtFatalMsg:
                txt = QString("Fatal: %1").arg(msg);
                break;
            case QtInfoMsg:
                txt = QString("Info: %1").arg(msg);
                break;
        }
        std::cerr << qPrintable(txt) << std::endl;
    }
};

//check if diff of two config files (.py) works
TEST_F(FileDiffTests, testDiffTool) {
    //set up
    int argc = 1;
    char *argv[1] = {new char('a')};


    QApplication a(argc, argv);
    QSharedPointer<CodeEditor> codeEditor_left(new CodeEditor);
    QSharedPointer<CodeEditor> codeEditor_right(new CodeEditor);

    QScopedPointer<FileDiff> diffTool(new FileDiff(codeEditor_left, codeEditor_right));
    diffTool->diff(file_left, file_right);
    QSignalSpy spy(&*diffTool, &FileDiff::sig_diffFinished);

    //Wait for signal
    spy.wait(50000);

    QString text_diff_left, text_diff_right;
    QString result_diff_left, result_diff_right;

    result_diff_left = codeEditor_left->toPlainText();
    result_diff_right = codeEditor_right->toPlainText();

    QFile inputFile_l(diff_left);
    inputFile_l.open(QIODevice::ReadOnly);
    QFile inputFile_r(diff_right);
    inputFile_r.open(QIODevice::ReadOnly);

    EXPECT_TRUE(inputFile_l.isOpen());
    QTextStream stream_l(&inputFile_l);
    QTextStream result_stream_l(&result_diff_left);
    EXPECT_TRUE(inputFile_r.isOpen());
    QTextStream stream_r(&inputFile_r);
    QTextStream result_stream_r(&result_diff_right);

    //Every line of pythons <<difflib>> generated result should be in the diff created here.

    //Verify left side
    QString line, line_result;
    do {
        EXPECT_TRUE(line == line_result);
        line = stream_l.readLine();
        line_result = result_stream_l.readLine();
    } while (!line.isNull() && !line_result.isNull());

    // Verify right side
    do {
        EXPECT_TRUE(line == line_result);
        line = stream_r.readLine();
        line_result = result_stream_r.readLine();
    } while (!line.isNull() && !line_result.isNull());

    //Signal should be emitted only once
    EXPECT_EQ(spy.count(), 1);

    QApplication::exit();
}