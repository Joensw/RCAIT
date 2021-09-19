#include <gtest/gtest.h>
#include <QSignalSpy>
#include <qapplication.h>
#include <mutex>
#include <QDir>
#include <QGraphicsItem>
#include <accuracycurve.h>
#include <classificationgraphics.h>
#include <confusionmatrix.h>
#include <topaccuraciesgraphics.h>


class MockGraphicsView : public GenericGraphicsView {

public:
    explicit MockGraphicsView(const QString &filePath)
            : GenericGraphicsView(nullptr, nullptr),
              m_filePath(filePath),
              m_graphicsFile(QFile(filePath)) {
    }

private:
    void setAccuracyCurve(const QSharedPointer<QGraphicsItem> &accuracyCurveImage) override {
        mock_handle();
    }

    void setConfusionMatrix(const QSharedPointer<QGraphicsItem> &matrixImage) override {
        mock_handle();
    }

    void setTopAccuraciesGraphics(const QSharedPointer<QGraphicsItem> &topAccuraciesImage) override {
        mock_handle();
    }

    void setClassificationGraphics(const QSharedPointer<QGraphicsItem> &classificationGraphicsImage) override {
        mock_handle();
    }

    void mock_handle() {
        EXPECT_TRUE(m_graphicsFile.exists());
        std::cerr << "\nGraphics generated. Check out graphics manually at "
                  << qPrintable(m_filePath) << "\n" << std::endl;
    }

    const QString &m_filePath;
    const QFile m_graphicsFile;
};

static volatile std::atomic_bool runOnce = true;

class ResultGraphicsTests : public testing::Test {

protected:
    QDir dir;

    //copy test files to new directory
    void SetUp() override {
        qInstallMessageHandler(myMessageHandler);
        dir = QDir(QDir::current().path());
        dir.mkpath("TEMP");
        dir.cd("TEMP");
        EXPECT_TRUE(dir.exists());

        if (runOnce) {
            //Cleanup
            for (const auto &item: dir.entryList()) {
                dir.remove(item);
            }
            EXPECT_TRUE(dir.isEmpty());
            runOnce = false;
        }
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

//check if generating accuracy curve graphics works
TEST_F(ResultGraphicsTests, testGraphics_AccuracyCurve) {
    //set up
    int argc = 1;
    char *argv[1] = {new char('a')};

    //Draw two checkmark [✓] symbols as curves
    QMap<int, QPair<double, double>> curve_data;
    for (int i = 1; i < 3; i++) {
        curve_data[i] = {80 - 30 * i, 90 - 30 * i};
    }
    for (int i = 3; i <= 6; i++) {
        curve_data[i] = {20 * i - 20, 20 * i - 10};
    }

    QApplication a(argc, argv);
    QScopedPointer<AccuracyCurve> graphics(new AccuracyCurve(dir.absolutePath(), "test", curve_data));
    QScopedPointer<MockGraphicsView> mockGraphicsView(new MockGraphicsView(graphics->getFullPath()));
    graphics->generateGraphics(&*mockGraphicsView);
    QSignalSpy spy(&*graphics, &GenericResultGraphics::sig_graphicsGenerated);

    //Wait for signal
    spy.wait(50000);

    //Signal should be emitted only once
    EXPECT_EQ(spy.count(), 1);
    QApplication::exit();
}

//check if generating classification graphics works
TEST_F(ResultGraphicsTests, testGraphics_Classification) {
    //set up
    int argc = 1;
    char *argv[1] = {new char('a')};

    //Map images to their confidence scores
    QMap<QString, QList<double>> classification_data{
            {"test_imagefolder/Auto/images.jpg",        {0.61, 0.39}},
            {"test_imagefolder/Auto/images_1.jpg",      {0.75, 0.25}},
            {"test_imagefolder/Flugzeug/airliner1.png", {0.03, 0.97}},
            {"test_imagefolder/Flugzeug/airliner2.png", {0.15, 0.85}},
    };
    static QStringList classification_labels = {"Auto", "Flugzeug"};

    QApplication a(argc, argv);
    QScopedPointer<ClassificationGraphics> graphics(
            new ClassificationGraphics(dir.absolutePath(), "test",
                                       classification_data, classification_labels));
    QScopedPointer<MockGraphicsView> mockGraphicsView(new MockGraphicsView(graphics->getFullPath()));
    graphics->generateGraphics(&*mockGraphicsView);
    QSignalSpy spy(&*graphics, &GenericResultGraphics::sig_graphicsGenerated);

    //Wait for signal
    spy.wait(50000);

    //Signal should be emitted only once
    EXPECT_EQ(spy.count(), 1);
    QApplication::exit();
}

//check if generating confusion matrix graphics works
TEST_F(ResultGraphicsTests, testGraphics_ConfusionMatrix) {
    //set up
    int argc = 1;
    char *argv[1] = {new char('a')};

    //Generate matrix contents and labels
    const QString alphabet = "ABCDEFGH";
    QStringList matrixLabels;
    std::copy(alphabet.begin(), alphabet.end(), std::back_inserter(matrixLabels));
    QList<int> matrixData;

    for (int i = 0; i < alphabet.size(); ++i) {
        for (int j = 0; j < alphabet.size(); ++j) {
            if (i == j)
                matrixData << (int) alphabet.size() + i - j;
            else
                matrixData << std::min(i, j) + 1;
        }
    }

    QApplication a(argc, argv);
    QScopedPointer<ConfusionMatrix> graphics(
            new ConfusionMatrix(dir.absolutePath(), "test", matrixLabels, matrixData));
    QScopedPointer<MockGraphicsView> mockGraphicsView(new MockGraphicsView(graphics->getFullPath()));
    graphics->generateGraphics(&*mockGraphicsView);
    QSignalSpy spy(&*graphics, &GenericResultGraphics::sig_graphicsGenerated);

    //Wait for signal
    spy.wait(50000);

    //Signal should be emitted only once
    EXPECT_EQ(spy.count(), 1);
    QApplication::exit();
}

//check if generating Top Accuracies' graphics works
TEST_F(ResultGraphicsTests, testGraphics_TopAccuracies) {
    //set up
    int argc = 1;
    char *argv[1] = {new char('a')};

    //Generate matrix contents and labels
    static QString alphabet = "ABCDEFGHIJKLMNOPQRSTUVWXYZ";

    QList<QPair<QString, QList<double>>> data;
    for (int i = 0; i < alphabet.size(); ++i) {
        data.append({alphabet[i], {i * 1.0, 1.0 * (double) alphabet.size() - i}});
    }

    QApplication a(argc, argv);
    QScopedPointer<TopAccuraciesGraphics> graphics(
            new TopAccuraciesGraphics(dir.absolutePath(), data));
    QScopedPointer<MockGraphicsView> mockGraphicsView(new MockGraphicsView(graphics->getFullPath()));
    graphics->generateGraphics(&*mockGraphicsView);
    QSignalSpy spy(&*graphics, &GenericResultGraphics::sig_graphicsGenerated);

    //Wait for signal
    spy.wait(50000);

    //Signal should be emitted only once
    EXPECT_EQ(spy.count(), 1);
    QApplication::exit();
}
