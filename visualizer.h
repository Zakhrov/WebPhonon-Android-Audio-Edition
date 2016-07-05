#ifndef VISUALIZER_H
#define VISUALIZER_H
#include <QOpenGLWidget>
#include <QWidget>
#include <QTimer>
#include <QImage>
#include <QMimeData>
#include <QOpenGLFunctions>
#include <QOpenGLTexture>
#include <QOpenGLShaderProgram>
#include <QQuaternion>
#include <QMatrix4x4>
#include <QOpenGLBuffer>

class Visualizer : public QOpenGLWidget, protected QOpenGLFunctions
{
    Q_OBJECT
public:
    Visualizer(QWidget *parent = 0);
    ~Visualizer();

protected:
    void initializeGL() Q_DECL_OVERRIDE;
      void resizeGL(int w, int h) Q_DECL_OVERRIDE;
      void paintGL() Q_DECL_OVERRIDE;
      void initShaders();




public slots:
    void animate();
private:
    void loadGLTexture();
    QOpenGLShaderProgram program;
    QOpenGLTexture *texture;
    QTimer *timer;
    QQuaternion rotation;
    float rotX,rotY,rotZ,rotA;
     QMatrix4x4 projection;
     void drawCubeGeometry(QOpenGLShaderProgram *program);
     void initCubeGeometry();

     QOpenGLBuffer arrayBuf;
     QOpenGLBuffer indexBuf;

};

#endif // VISUALIZER_H
