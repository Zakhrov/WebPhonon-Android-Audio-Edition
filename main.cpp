#include "mainwindow.h"
#include <QApplication>

int main(int argc, char *argv[])
{
    QApplication a(argc, argv);
    QSurfaceFormat format;
    format.setDepthBufferSize( 4 );
    format.setSamples(24);
    format.setRenderableType(QSurfaceFormat::OpenGL);
    MainWindow w;
    w.showMaximized();

    return a.exec();
}
