
#include <glad/glad.h>
#include <glfw/glfw3.h>
#include <iostream>
#include <string>
#include "user/data.h"
#include "user/glProg.h"
#include "user/initWindow.h"


extern GLFWwindow *window;

//----------MAIN STARTS--------------------------

int main()
{
  initWinGlfw();
  std::string vertex_shader_source = parseShader( "./res/shaders/shader.vert" );
  std::string fragment_shader_source =
      parseShader( "./res/shaders/shader.frag" );
  createProgram( vertex_shader_source, fragment_shader_source );
  std::cout << glGetString( GL_VERSION );

  
  unsigned int vbo, vao, ebo;
  glGenVertexArrays( 1, &vao );
  glBindVertexArray( vao );

  glGenBuffers( 1, &vbo );
  glBindBuffer( GL_ARRAY_BUFFER, vbo );
  glBufferData( GL_ARRAY_BUFFER, sizeof( vertices ), vertices, GL_STATIC_DRAW );

  glGenBuffers( 1, &ebo );
  glBindBuffer( GL_ELEMENT_ARRAY_BUFFER, ebo );
  glBufferData( GL_ELEMENT_ARRAY_BUFFER, sizeof( indices ), indices,
                GL_STATIC_DRAW );

  // bind array data to shader
  glVertexAttribPointer( 0, 3, GL_FLOAT, GL_FALSE, 3 * sizeof( float ),
                         (void *)0 );
  glEnableVertexAttribArray( 0 );
  glVertexAttribPointer( 1, 4, GL_FLOAT, GL_FALSE, sizeof( float ),
                         (void *)( 12 * sizeof( float ) ) );
  glEnableVertexAttribArray( 1 );

  glClearColor( 0.3f, 0.3f, 0.3f, 1.0f );

  while ( !glfwWindowShouldClose( window ) )  // todo: make compatable with sdl?
  {
    int width, height;
    glfwGetFramebufferSize( window, &width, &height );

    glClear( GL_COLOR_BUFFER_BIT );
    glDrawElements( GL_TRIANGLES, 6, GL_UNSIGNED_INT, 0 );

    glfwSwapBuffers( window );
    glfwWaitEvents();
  }
}

//--------------------END MAIN------------------------------------
