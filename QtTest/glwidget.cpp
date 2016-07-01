// Include standard headers
#include <windows.h>
#include <stdio.h>
#include <stdlib.h>

//Include GLEW before GLFW
#include <GL/glew.h>

#define GLFW_INCLUDE_GLEXT
#include <GLFW\glfw3.h>
GLFWwindow* window1;

// Include GLM
#include <glm/glm.hpp>
using namespace glm;

#include <string>
#include <vector>
#include <iostream>
#include <fstream>
#include <algorithm>
using namespace std;

#include <stdlib.h>
#include <string.h>

#include "glwidget.h"

GLWidget::GLWidget( const QGLFormat& format, QWidget* parent )
    : QGLWidget( format, parent ),
      m_vertexBuffer( QGLBuffer::VertexBuffer )
{
}

void GLWidget::initializeGL()
{

          // Initialise GLFW
          if( !glfwInit() )
          {
                  fprintf( stderr, "Failed to initialize GLFW\n" );
                  getchar();
          }

          glfwWindowHint(GLFW_SAMPLES, 4);
          glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 3);
          glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 3);
          glfwWindowHint(GLFW_OPENGL_FORWARD_COMPAT, GL_TRUE); // To make MacOS happy; should not be needed
          glfwWindowHint(GLFW_OPENGL_PROFILE, GLFW_OPENGL_CORE_PROFILE);

          // Open a window and create its OpenGL context
          window1 = glfwCreateWindow( 1024, 768, "Tutorial 02 - Red triangle", NULL, NULL);
          if( window1 == NULL ){
                  fprintf( stderr, "Failed to open GLFW window. If you have an Intel GPU, they are not 3.3 compatible. Try the 2.1 version of the tutorials.\n" );
                  getchar();
                  glfwTerminate();
          }
          glfwMakeContextCurrent(window1);

          // Initialize GLEW
          glewExperimental = true; // Needed for core profile
          if (glewInit() != GLEW_OK) {
                  fprintf(stderr, "Failed to initialize GLEW\n");
                  getchar();
                  glfwTerminate();
          }

          // Ensure we can capture the escape key being pressed below
          glfwSetInputMode(window1, GLFW_STICKY_KEYS, GL_TRUE);

          // Dark blue background
          glClearColor(0.0f, 0.0f, 0.4f, 0.0f);

          GLuint VertexArrayID;
          glGenVertexArrays(1, &VertexArrayID);
          glBindVertexArray(VertexArrayID);

          // Create and compile our GLSL program from the shaders
          GLuint programID = LoadShaders( "SimpleVertexShader.vertexshader", "SimpleFragmentShader.fragmentshader" );


          static const GLfloat g_vertex_buffer_data[] = {
                  -1.0f, -1.0f, 0.0f,
                   1.0f, -1.0f, 0.0f,
                   0.0f,  1.0f, 0.0f,
          };

          GLuint vertexbuffer;
          glGenBuffers(1, &vertexbuffer);
          glBindBuffer(GL_ARRAY_BUFFER, vertexbuffer);
          glBufferData(GL_ARRAY_BUFFER, sizeof(g_vertex_buffer_data), g_vertex_buffer_data, GL_STATIC_DRAW);

          //do{

                  // Clear the screen
                  glClear( GL_COLOR_BUFFER_BIT );

                  // Use our shader
                  glUseProgram(programID);

                  // 1rst attribute buffer : vertices
                  glEnableVertexAttribArray(0);
                  glBindBuffer(GL_ARRAY_BUFFER, vertexbuffer);
                  glVertexAttribPointer(
                          0,                  // attribute 0. No particular reason for 0, but must match the layout in the shader.
                          3,                  // size
                          GL_FLOAT,           // type
                          GL_FALSE,           // normalized?
                          0,                  // stride
                          (void*)0            // array buffer offset
                  );

                  // Draw the triangle !
                  glDrawArrays(GL_TRIANGLES, 0, 3); // 3 indices starting at 0 -> 1 triangle

                  glDisableVertexAttribArray(0);

                  // Swap buffers
                  glfwSwapBuffers(window1);
                  glfwPollEvents();

       //   }

          // Cleanup VBO
          glDeleteBuffers(1, &vertexbuffer);
          glDeleteVertexArrays(1, &VertexArrayID);
          glDeleteProgram(programID);

          // Close OpenGL window and terminate GLFW
          glfwTerminate();

          //return 0;


}

void GLWidget::resizeGL( int w, int h )
{
    // Set the viewport to window dimensions
   // glViewport( 0, 0, w, qMax( h, 1 ) );

   std::cout << "resize" << std::endl;
}

void GLWidget::paintGL()
{
  std::cout << "paint" << std::endl;
}



GLuint GLWidget::LoadShaders(const char * vertex_file_path,const char * fragment_file_path){

	// Create the shaders
	GLuint VertexShaderID = glCreateShader(GL_VERTEX_SHADER);
	GLuint FragmentShaderID = glCreateShader(GL_FRAGMENT_SHADER);

	// Read the Vertex Shader code from the file
	std::string VertexShaderCode;
	std::ifstream VertexShaderStream(vertex_file_path, std::ios::in);
	if(VertexShaderStream.is_open()){
		std::string Line = "";
		while(getline(VertexShaderStream, Line))
			VertexShaderCode += "\n" + Line;
		VertexShaderStream.close();
	}else{
		printf("Impossible to open %s. Are you in the right directory ? Don't forget to read the FAQ !\n", vertex_file_path);
		getchar();
		return 0;
	}

	// Read the Fragment Shader code from the file
	std::string FragmentShaderCode;
	std::ifstream FragmentShaderStream(fragment_file_path, std::ios::in);
	if(FragmentShaderStream.is_open()){
		std::string Line = "";
		while(getline(FragmentShaderStream, Line))
			FragmentShaderCode += "\n" + Line;
		FragmentShaderStream.close();
	}

	GLint Result = GL_FALSE;
	int InfoLogLength;


	// Compile Vertex Shader
	printf("Compiling shader : %s\n", vertex_file_path);
	char const * VertexSourcePointer = VertexShaderCode.c_str();
	glShaderSource(VertexShaderID, 1, &VertexSourcePointer , NULL);
	glCompileShader(VertexShaderID);

	// Check Vertex Shader
	glGetShaderiv(VertexShaderID, GL_COMPILE_STATUS, &Result);
	glGetShaderiv(VertexShaderID, GL_INFO_LOG_LENGTH, &InfoLogLength);
	if ( InfoLogLength > 0 ){
		std::vector<char> VertexShaderErrorMessage(InfoLogLength+1);
		glGetShaderInfoLog(VertexShaderID, InfoLogLength, NULL, &VertexShaderErrorMessage[0]);
		printf("%s\n", &VertexShaderErrorMessage[0]);
	}



	// Compile Fragment Shader
	printf("Compiling shader : %s\n", fragment_file_path);
	char const * FragmentSourcePointer = FragmentShaderCode.c_str();
	glShaderSource(FragmentShaderID, 1, &FragmentSourcePointer , NULL);
	glCompileShader(FragmentShaderID);

	// Check Fragment Shader
	glGetShaderiv(FragmentShaderID, GL_COMPILE_STATUS, &Result);
	glGetShaderiv(FragmentShaderID, GL_INFO_LOG_LENGTH, &InfoLogLength);
	if ( InfoLogLength > 0 ){
		std::vector<char> FragmentShaderErrorMessage(InfoLogLength+1);
		glGetShaderInfoLog(FragmentShaderID, InfoLogLength, NULL, &FragmentShaderErrorMessage[0]);
		printf("%s\n", &FragmentShaderErrorMessage[0]);
	}

	// Link the program
	printf("Linking program\n");
	GLuint ProgramID = glCreateProgram();
	glAttachShader(ProgramID, VertexShaderID);
	glAttachShader(ProgramID, FragmentShaderID);
	glLinkProgram(ProgramID);

	// Check the program
	glGetProgramiv(ProgramID, GL_LINK_STATUS, &Result);
	glGetProgramiv(ProgramID, GL_INFO_LOG_LENGTH, &InfoLogLength);
	if ( InfoLogLength > 0 ){
		std::vector<char> ProgramErrorMessage(InfoLogLength+1);
		glGetProgramInfoLog(ProgramID, InfoLogLength, NULL, &ProgramErrorMessage[0]);
		printf("%s\n", &ProgramErrorMessage[0]);
	}


	glDetachShader(ProgramID, VertexShaderID);
	glDetachShader(ProgramID, FragmentShaderID);

	glDeleteShader(VertexShaderID);
	glDeleteShader(FragmentShaderID);

	return ProgramID;
}
