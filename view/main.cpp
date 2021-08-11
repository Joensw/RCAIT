#include "view/mainwindow.h"
#include <QApplication>
#include <QStyleFactory>
#include <controller.h>

int main(int argc, char *argv[])
{
    QApplication a(argc, argv);

    //Set UI style and font
    QApplication::setStyle(QStyleFactory::create("fusion"));
    QPalette palette = QApplication::palette();
    //Base color
    palette.setColor(QPalette::Highlight, QColor("royal blue"));
    QApplication::setPalette(palette);

    QFontDatabase::addApplicationFont(":/Resources/Fonts/Inter-Regular.otf");
    QFont sf_pro_text("Inter");
    sf_pro_text.setPixelSize(12);
    sf_pro_text.setHintingPreference(QFont::HintingPreference::PreferNoHinting); //This line did the trick
    QApplication::setFont(sf_pro_text);

    QCoreApplication::setOrganizationName("PSE_SS21");
    QCoreApplication::setApplicationName("RCAIT");

    Controller controller;

    return QApplication::exec();
}
