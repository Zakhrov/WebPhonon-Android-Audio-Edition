#include "visualizer.h"
struct VertexData
{
    QVector3D position;
    QVector2D texCoord;
};
Visualizer::Visualizer(QWidget *parent)
    : QOpenGLWidget(parent),indexBuf(QOpenGLBuffer::IndexBuffer)
{

    setCursor(Qt::BlankCursor);
    setFocus();
        timer=new QTimer(this);
         timer->setInterval(1);
         connect(timer,SIGNAL(timeout()),this,SLOT(animate()));
         timer->start();
         rotX=rotY=rotZ=rotA=1;

}

Visualizer::~Visualizer()
{
    arrayBuf.destroy();
       indexBuf.destroy();
       makeCurrent();
          delete texture;
          doneCurrent();
}
void Visualizer::initializeGL()
{

    initializeOpenGLFunctions();
    glClearColor(0, 0, 0, 1);

        initShaders();
        loadGLTexture();

        // Enable depth buffer
        glEnable(GL_DEPTH_TEST);

        // Enable back face culling
        glEnable(GL_CULL_FACE);



}

void Visualizer::paintGL()
{
    // Clear color and depth buffer
       glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

       texture->bind();

       // Calculate model view transformation
       QMatrix4x4 matrix;
       matrix.translate(0.0, 0.0, -5.0);
       matrix.rotate(rotation);

       // Set modelview-projection matrix
       program.setUniformValue("mvp_matrix", projection * matrix);

       // Use texture unit 0 which contains cube.png
       program.setUniformValue("texture", 0);

       // Generate 2 VBOs
       arrayBuf.create();
       indexBuf.create();

       // Initializes cube geometry and transfers it to VBOs
       initCubeGeometry();
       drawCubeGeometry(&program);


}

void Visualizer::initShaders()
{
    // Compile vertex shader
        if (!program.addShaderFromSourceFile(QOpenGLShader::Vertex, ":/vshader.vsh"))
            close();

        // Compile fragment shader
        if (!program.addShaderFromSourceFile(QOpenGLShader::Fragment, ":/fshader.fsh"))
            close();

        // Link shader pipeline
        if (!program.link())
            close();

        // Bind shader pipeline for use
        if (!program.bind())
            close();
}

void Visualizer::resizeGL(int w, int h)
{
    // Calculate aspect ratio
        qreal aspect = qreal(w) / qreal(h ? h : 1);

        // Set near plane to 3.0, far plane to 7.0, field of view 45 degrees
        const qreal zNear = 3.0, zFar = 7.0, fov = 45.0;

        // Reset projection
        projection.setToIdentity();

        // Set perspective projection
        projection.perspective(fov, aspect, zNear, zFar);
}



void Visualizer::animate()
{

    rotation *= QQuaternion::fromAxisAndAngle(rotX,rotY,rotZ,1);
    update();
}

void Visualizer::loadGLTexture()
{
    // Load cube.png image
       texture = new QOpenGLTexture(QImage(":/splash/WebPhonon-Master-text2.png").mirrored());

       // Set nearest filtering mode for texture minification
       texture->setMinificationFilter(QOpenGLTexture::Nearest);

       // Set bilinear filtering mode for texture magnification
       texture->setMagnificationFilter(QOpenGLTexture::Linear);

       // Wrap texture coordinates by repeating
       // f.ex. texture coordinate (1.1, 1.2) is same as (0.1, 0.2)
       texture->setWrapMode(QOpenGLTexture::Repeat);
}

void Visualizer::drawCubeGeometry(QOpenGLShaderProgram *program)
{
    // Tell OpenGL which VBOs to use
       arrayBuf.bind();
       indexBuf.bind();

       // Offset for position
       quintptr offset = 0;

       // Tell OpenGL programmable pipeline how to locate vertex position data
       int vertexLocation = program->attributeLocation("a_position");
       program->enableAttributeArray(vertexLocation);
       program->setAttributeBuffer(vertexLocation, GL_FLOAT, offset, 3, sizeof(VertexData));

       // Offset for texture coordinate
       offset += sizeof(QVector3D);

       // Tell OpenGL programmable pipeline how to locate vertex texture coordinate data
       int texcoordLocation = program->attributeLocation("a_texcoord");
       program->enableAttributeArray(texcoordLocation);
       program->setAttributeBuffer(texcoordLocation, GL_FLOAT, offset, 2, sizeof(VertexData));

       // Draw cube geometry using indices from VBO 1
       glDrawElements(GL_TRIANGLE_STRIP, 34, GL_UNSIGNED_SHORT, 0);
}

void Visualizer::initCubeGeometry()
{
    // For cube we would need only 8 vertices but we have to
       // duplicate vertex for each face because texture coordinate
       // is different.
       VertexData vertices[] = {
           // Vertex data for face 0
           {QVector3D(-1.0f, -1.0f,  1.0f), QVector2D(0.0f, 0.0f)},  // v0
           {QVector3D( 1.0f, -1.0f,  1.0f), QVector2D(1.0f, 0.0f)}, // v1
           {QVector3D(-1.0f,  1.0f,  1.0f), QVector2D(0.0f, 1.0f)},  // v2
           {QVector3D( 1.0f,  1.0f,  1.0f), QVector2D(1.0f, 1.0f)}, // v3

           // Vertex data for face 1
           {QVector3D( 1.0f, -1.0f,  1.0f), QVector2D( 0.0f, 0.0f)}, // v4
           {QVector3D( 1.0f, -1.0f, -1.0f), QVector2D(1.0f, 0.0f)}, // v5
           {QVector3D( 1.0f,  1.0f,  1.0f), QVector2D(0.0f, 1.0f)},  // v6
           {QVector3D( 1.0f,  1.0f, -1.0f), QVector2D(1.0f, 1.0f)}, // v7

           // Vertex data for face 2
           {QVector3D( 1.0f, -1.0f, -1.0f), QVector2D(0.0f, 0.0f)}, // v8
           {QVector3D(-1.0f, -1.0f, -1.0f), QVector2D(1.0f, 0.0f)},  // v9
           {QVector3D( 1.0f,  1.0f, -1.0f), QVector2D(0.0f, 1.0f)}, // v10
           {QVector3D(-1.0f,  1.0f, -1.0f), QVector2D(1.0f, 1.0f)},  // v11

           // Vertex data for face 3
           {QVector3D(-1.0f, -1.0f, -1.0f), QVector2D(0.0f, 0.0f)}, // v12
           {QVector3D(-1.0f, -1.0f,  1.0f), QVector2D(1.0f, 0.0f)},  // v13
           {QVector3D(-1.0f,  1.0f, -1.0f), QVector2D(0.0f, 1.0f)}, // v14
           {QVector3D(-1.0f,  1.0f,  1.0f), QVector2D(1.0f, 1.0f)},  // v15

           // Vertex data for face 4
           {QVector3D(-1.0f, -1.0f, -1.0f), QVector2D(0.0f, 0.0f)}, // v16
           {QVector3D( 1.0f, -1.0f, -1.0f), QVector2D(1.0f, 0.0f)}, // v17
           {QVector3D(-1.0f, -1.0f,  1.0f), QVector2D(0.0f, 1.0f)}, // v18
           {QVector3D( 1.0f, -1.0f,  1.0f), QVector2D(1.0f, 1.0f)}, // v19

           // Vertex data for face 5
           {QVector3D(-1.0f,  1.0f,  1.0f), QVector2D(0.0f, 0.0f)}, // v20
           {QVector3D( 1.0f,  1.0f,  1.0f), QVector2D(1.0f, 0.0f)}, // v21
           {QVector3D(-1.0f,  1.0f, -1.0f), QVector2D(0.0f, 1.0f)}, // v22
           {QVector3D( 1.0f,  1.0f, -1.0f), QVector2D(1.0f, 1.0f)}  // v23
       };

       // Indices for drawing cube faces using triangle strips.
       // Triangle strips can be connected by duplicating indices
       // between the strips. If connecting strips have opposite
       // vertex order then last index of the first strip and first
       // index of the second strip needs to be duplicated. If
       // connecting strips have same vertex order then only last
       // index of the first strip needs to be duplicated.
       GLushort indices[] = {
            0,  1,  2,  3,  3,     // Face 0 - triangle strip ( v0,  v1,  v2,  v3)
            4,  4,  5,  6,  7,  7, // Face 1 - triangle strip ( v4,  v5,  v6,  v7)
            8,  8,  9, 10, 11, 11, // Face 2 - triangle strip ( v8,  v9, v10, v11)
           12, 12, 13, 14, 15, 15, // Face 3 - triangle strip (v12, v13, v14, v15)
           16, 16, 17, 18, 19, 19, // Face 4 - triangle strip (v16, v17, v18, v19)
           20, 20, 21, 22, 23      // Face 5 - triangle strip (v20, v21, v22, v23)
       };

       // Transfer vertex data to VBO 0
       arrayBuf.bind();
       arrayBuf.allocate(vertices, 24 * sizeof(VertexData));

       // Transfer index data to VBO 1
       indexBuf.bind();
       indexBuf.allocate(indices, 34 * sizeof(GLushort));
}

