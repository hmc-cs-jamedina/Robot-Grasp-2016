#ifndef GLWIDGET_H
#define GLWIDGET_H

#include <QGLWidget>

#include <QGLBuffer>
#include <QGLShaderProgram>

// Include GLM
#define GLM_FORCE_RADIANS
#include <glm/glm.hpp>
#include <glm/gtc/matrix_transform.hpp>
using namespace glm;

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
    void computeMatricesFromInputs();\
    bool loadOBJ( const char * path,
                  std::vector<glm::vec3> & out_vertices,
                  std::vector<glm::vec2> & out_uvs,
                  std::vector<glm::vec3> & out_normals );

    std::vector<glm::vec3> vertices;
    std::vector<glm::vec2> uvs;
    std::vector<glm::vec3> normals;

    GLuint uvbuffer;
    GLuint normalbuffer;

    GLuint programID;
    GLuint vertexbuffer;
    QGLBuffer m_vertexBuffer;
    GLuint vertex_buffer_data[];

     GLuint LightID;
    GLuint MatrixID;
    GLuint ViewMatrixID;
    GLuint ModelMatrixID;
    glm::mat4 ViewMatrix;
    glm::mat4 ProjectionMatrix;
};

#endif // GLWIDGET_H
