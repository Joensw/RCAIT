#include "view/mainwindow.h"
#include <QApplication>
#include <QStyleFactory>
#include <controller.h>

/**
 * @brief Main method and entry point of the application
 * @param argc contains the launch command as int
 * @param argv contains the launch arguments as an array
 * @return exit code of the application
 */
int main(int argc, char *argv[]) {
    QApplication a(argc, argv);

    //Load fonts
    QFontDatabase::addApplicationFont(":/Fonts/Inter-Regular.otf");
    QFontDatabase::addApplicationFont(":/Fonts/InterMonospace-Medium.otf");

    //Set UI style and font
    QApplication::setStyle(QStyleFactory::create("fusion"));
    //Base color
    QPalette palette = QApplication::palette();
    palette.setColor(QPalette::Highlight, QColor(1, 109, 255));
    QApplication::setPalette(palette);

    //Font
    QFont inter("Inter", 8);
    inter.setHintingPreference(QFont::HintingPreference::PreferNoHinting);
    QApplication::setFont(inter);

    QCoreApplication::setOrganizationName("PSE_SS21");
    QCoreApplication::setApplicationName("RCAIT");

    Controller controller;

    return QApplication::exec();
}
