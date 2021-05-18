#include "mainwindow.h"

#include <QApplication>
#include <QLocale>
#include <QTranslator>
#include <QStyleFactory>
#include <QFontDatabase>

int main(int argc, char *argv[])
{
    QApplication a(argc, argv);

    //Set UI style and font
    QApplication::setStyle(QStyleFactory::create("fusion"));
    QFontDatabase::addApplicationFont(":/Resources/Fonts/SF-Pro-Text-Regular.otf");
    QFont sf_pro_text("SF Pro Text");
    sf_pro_text.setPixelSize(12);
    sf_pro_text.setHintingPreference(QFont::HintingPreference::PreferNoHinting); //This line did the trick
    QApplication::setFont(sf_pro_text);

    MainWindow w;
    w.show();
    return a.exec();
}
