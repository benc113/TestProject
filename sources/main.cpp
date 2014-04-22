#include "testwidget.h"
#include <QApplication>

#include <QFontDatabase>

int main(int argc, char *argv[])
{
    QApplication a(argc, argv);

    //set-up font
    QFontDatabase::addApplicationFont("://Assets/font/AlternateGotNo3D.ttf");

    TestWidget w;
    w.show();

    return a.exec();
}
