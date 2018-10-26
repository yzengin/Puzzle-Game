#include <QApplication>

#include "mainwindow.h"

int main(int argc, char *argv[])
{
    QApplication app(argc, argv);
    MainWindow window;
    window.resimYukle(QStringLiteral(":/resim/puzzle.jpg"));
    window.show();
    return app.exec();
}
