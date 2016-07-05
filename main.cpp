#include "mainwindow.h"
#include <QApplication>
#include <QStyleFactory>
int main(int argc, char *argv[])
{
    QApplication a(argc, argv);
    QSurfaceFormat format;
    format.setDepthBufferSize( 4 );
    format.setSamples(24);
    format.setRenderableType(QSurfaceFormat::OpenGL);
    a.setStyle(QStyleFactory::create("Android"));
    MainWindow w;
    w.showMaximized();

    return a.exec();
}
