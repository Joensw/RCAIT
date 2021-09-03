#include "view/mainwindow.h"
#include <QApplication>
#include <QStyleFactory>
#include <controller.h>

int main(int argc, char *argv[]) {
    QApplication a(argc, argv);

    //Load fonts
    QFontDatabase::addApplicationFont(":/Fonts/Inter-Regular.otf");
    QFontDatabase::addApplicationFont(":/Fonts/InterMonospace-Medium.otf");

    //Set UI style and font
    QApplication::setStyle(QStyleFactory::create("fusion"));
    QPalette palette = QApplication::palette();
    //Base color
    palette.setColor(QPalette::Highlight, QColor("royal blue"));
    QApplication::setPalette(palette);

    QFont inter("Inter", 9);
    inter.setHintingPreference(QFont::HintingPreference::PreferNoHinting);
    QApplication::setFont(inter);

    QCoreApplication::setOrganizationName("PSE_SS21");
    QCoreApplication::setApplicationName("RCAIT");

    Controller controller;

    return QApplication::exec();
}
