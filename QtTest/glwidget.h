#ifndef GLWIDGET_H
#define GLWIDGET_H

#include <QGLWidget>

#include <QGLBuffer>
#include <QGLShaderProgram>

class GLWidget : public QGLWidget
{
    Q_OBJECT
public:
    GLWidget( const QGLFormat& format, QWidget* parent = 0 );

protected:
    virtual void initializeGL();
    virtual void resizeGL( int w, int h );
    virtual void paintGL();

    GLuint LoadShaders(const char * vertex_file_path,const char * fragment_file_path);

private:
    //bool prepareShaderProgram( const QString& vertexShaderPath,
//                               const QString& fragmentShaderPath );

    GLuint vertex_buffer_data[];
    GLuint programID;
    GLuint vertexbuffer;
    QGLShaderProgram m_shader;
    QGLBuffer m_vertexBuffer;
    QGLBuffer m_normalBuffer;
};

#endif // GLWIDGET_H
