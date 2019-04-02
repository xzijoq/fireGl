
#include <glad/glad.h>
#include <glfw/glfw3.h>
#include <filesystem>
#include <iostream>
#include <string>
#include "user/data.h"
#include "user/glProg.h"
#include "user/initWindow.h"

namespace fs = std::filesystem;
using std::string;

using std::cout;
extern GLFWwindow * window;
void                display();
void                initGl();
static unsigned int vbo{333}, vao{333}, ebo{333};

std::string retS()
{//This is Deadly Inefficeient, but does not contribute
  std::string fp = __FILE__;
  std::string tr( "\\" );
  std::string th( "\/" );
  int ls{0};
  size_t pos{0};
  // For loop for windows repalce path
  for ( auto i{0}; i < fp.length(); i++ )
  {
    pos = fp.find( tr );
    if ( pos == string::npos ) { break; }
    fp.replace( pos, tr.length(), "\/" );
  }

  // remove from second last directory
  for ( auto j{0}; j < 2; j++ )
  {
    for ( auto i{0}; i < fp.length(); i++ )
    {
      pos = fp.find( th, pos + 1 );

      if ( pos != string::npos ) { ls = pos; }
      if ( pos == string::npos )
      {
        fp.erase( ls, -12 );
        break;
      }
    }
  }
  return fp;
}

//----------MAIN STARTS--------------------------

int main()
{
  string wd = retS();

  initWinGlfw();
  std::string vertex_shader_source = parseShader(wd + "/res/shaders/shader.vert" );
  std::string fragment_shader_source =
      parseShader(wd + "/res/shaders/shader.frag" );
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
