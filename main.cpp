#include "mainwindow.h"

#include <QApplication>
#include <QLocale>
#include <QTranslator>
#include <QStyleFactory>
#include <QFontDatabase>

int main(int argc, char *argv[])
{
    QApplication a(argc, argv);

    QApplication::setStyle(QStyleFactory::create("fusion"));
    QFontDatabase::addApplicationFont(":/Resources/Fonts/SF-Pro-Text-Regular.otf");
    QFont sf_pro_text("SF Pro Text");
    sf_pro_text.setPixelSize(12);
    sf_pro_text.setHintingPreference(QFont::HintingPreference::PreferNoHinting); //This line did the trick
    QApplication::setFont(sf_pro_text);


    QTranslator translator;
    const QStringList uiLanguages = QLocale::system().uiLanguages();
    for (const QString &locale : uiLanguages) {
        const QString baseName = "ui-test_" + QLocale(locale).name();
        if (translator.load(":/i18n/" + baseName)) {
            a.installTranslator(&translator);
            break;
        }
    }
    MainWindow w;
    w.show();
    return a.exec();
}
