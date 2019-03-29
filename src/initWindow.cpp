#include "user/initWindow.h"
#include <iostream>
using std::cout;
GLFWwindow* window = nullptr;

void set_glfw_callbacks();

void initWinGlfw()
{
  if ( !glfwInit() ) cout << "GLFW failed to initialize";

  // glfw hints
  glfwWindowHint( GLFW_CONTEXT_VERSION_MAJOR, windowData::oglMajor );
  glfwWindowHint( GLFW_CONTEXT_VERSION_MINOR, windowData::oglMinor );
  glfwWindowHint( GLFW_OPENGL_PROFILE, GLFW_OPENGL_CORE_PROFILE );

  // window creation
  window = glfwCreateWindow( windowData::scWid, windowData::scHei, "uo", 0, 0 );
  if ( !window ) cout << "glfwWindow Creation Failed";

  glfwMakeContextCurrent( window );
  gladLoadGLLoader( (GLADloadproc)glfwGetProcAddress );

  set_glfw_callbacks();
}

void win_close_glfwCB( GLFWwindow* win )
{
  std::cout << "\n closing Glfw window: \n";
  // glfwTerminate();	 //gives segFault as it's alreay destroyes prolyy
}

void err_glfwCB( int error, const char* description )
{
  cout << "glfw error call back called :" << error << ":: " << description;
}

void key_glfwCB( GLFWwindow* window, int key, int scancode, int action,
                 int mods )
{
  if ( key == GLFW_KEY_ESCAPE && action == GLFW_PRESS )
  { glfwSetWindowShouldClose( window, true ); }
}
void fb_resize_glfwCB( GLFWwindow* window, int width, int height )
{
  glViewport( 0, 0, width, height );
}
void set_glfw_callbacks()
{
  glfwSetWindowCloseCallback( window, win_close_glfwCB );
  glfwSetErrorCallback( err_glfwCB );
  glfwSetKeyCallback( window, key_glfwCB );
  glfwSetFramebufferSizeCallback( window, fb_resize_glfwCB );
}
