
#include <glad/glad.h>
#include <glfw/glfw3.h>
#include <iostream>
#include <string>
#include "user/data.h"
#include "user/glProg.h"
#include "user/initWindow.h"


extern GLFWwindow *window;
void display();



float linea[] = {
    0.0f, 0.0f, 0.0f,  // p1
    0.0f, 0.9f, 0.0f   // p2
};

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

  unsigned int lineq{333};
  glGenBuffers( 1, &lineq );
  glBindBuffer( GL_ARRAY_BUFFER, lineq );
  glBufferData( GL_ARRAY_BUFFER, sizeof( linea ), linea, GL_STATIC_DRAW );

  // bind array data to shader
  glVertexAttribPointer( 0, 3, GL_FLOAT, GL_TRUE, 3 * sizeof( float ),
                         (void *)0 );
  //glVertexAttribPointer()                         
  glEnableVertexAttribArray( 0 );
  // glVertexAttribPointer( 1, 4, GL_FLOAT, GL_FALSE, sizeof( float ),
  //                        (void *)( 12 * sizeof( float ) ) );
  glEnableVertexAttribArray( 1 );

  glClearColor( 0.3f, 0.3f, 0.3f, 1.0f );
  

  while ( !glfwWindowShouldClose( window ) )  // todo: make compatable with sdl?
  {
    int width, height;
    glfwGetFramebufferSize( window, &width, &height );
    display();

    glfwSwapBuffers( window );
    glfwWaitEvents();
  }
}

//--------------------END MAIN------------------------------------

void display(){

    glClear( GL_COLOR_BUFFER_BIT );
    for(float i{0.0};i<1;i=i+0.04)
    { linea[1]=i;
      
      glBufferData( GL_ARRAY_BUFFER, sizeof( linea ), linea, GL_STATIC_DRAW );
      glDrawElements( GL_POINTS, 2, GL_UNSIGNED_INT, 0 );
    }
  
}
