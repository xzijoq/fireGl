
#include <glad/glad.h>
#include <glfw/glfw3.h>
#include <iostream>
#include <string>
#include "user/data.h"
#include "user/glProg.h"
#include "user/initWindow.h"


using std::string,std::cout;

extern GLFWwindow * window;
void                display();
void                initGl();
static unsigned int vbo{333}, vao{333}, ebo{333};

//----------MAIN STARTS--------------------------

int main()
{
  std::string Pd = ProjDir();
  initWinGlfw();
  std::string vertex_shader_source =
      parseShader( Pd + "/res/shaders/shader.vert" );
  std::string fragment_shader_source =
      parseShader( Pd + "/res/shaders/shader.frag" );
  createProgram( vertex_shader_source, fragment_shader_source );
  std::cout << glGetString( GL_VERSION );
  static int width{333}, height{333};
  initGl();
  while ( !glfwWindowShouldClose( window ) )  // todo: make compatable with sdl?
  {
    glfwGetFramebufferSize( window, &width, &height );

    display();

    glfwSwapBuffers( window );
    glfwWaitEvents();
  }
}

void display()
{
  glBindVertexArray( vao );
  glClear( GL_COLOR_BUFFER_BIT );
  glDrawArrays( GL_TRIANGLES, 0, 6 );
  // glDrawElements( GL_TRIANGLES, 2, GL_UNSIGNED_INT, 0 );
}

void initGl()
{
  static const float verticesa[] = {-0.90f, -0.90f, 0.85f, -0.90,
                                    -0.90f, 0.85f,  // Triangle 1
                                    0.90f,  -0.85f, 0.90f, 0.90f,
                                    -0.85f, 0.90f

  };
  glGenVertexArrays( 1, &vao );
  glBindVertexArray( vao );

  glGenBuffers( 1, &vbo );
  glBindBuffer( GL_ARRAY_BUFFER, vbo );
  glBufferData( GL_ARRAY_BUFFER, sizeof( verticesa ), verticesa,
                GL_STATIC_DRAW );

  // bind array data to shader
  glVertexAttribPointer( 0, 2, GL_FLOAT, GL_FALSE, 2 * sizeof( float ),
                         (void *)0 );
  glEnableVertexAttribArray( 0 );

  glClearColor( 0.3f, 0.3f, 0.3f, 1.0f );
}

//--------------------END MAIN------------------------------------


/*
  glGenBuffers( 1, &ebo );
  glBindBuffer( GL_ELEMENT_ARRAY_BUFFER, ebo );
  glBufferData( GL_ELEMENT_ARRAY_BUFFER, sizeof( indices ), indices,
               GL_STATIC_DRAW );
        glVertexAttribPointer(1, 4, GL_FLOAT, GL_FALSE, sizeof( float ), (void
  *)( 12 * sizeof( float ) ) ); glEnableVertexAttribArray( 1 );
 */
