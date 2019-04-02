
#include <glad/glad.h>
#include <glfw/glfw3.h>
#include <fstream>
#include <iostream>
#include <sstream>
#include <string>
//#include "user/data.h"
#include "user/glProg.h"
#include "user/initWindow.h"

unsigned int createProgram( const std::string &vertexShaderSource,
                            const std::string &fragmentShaderSource )
{
  unsigned int pid = glCreateProgram();
  unsigned int vsId = compileShader( GL_VERTEX_SHADER, vertexShaderSource );
  unsigned int fsId = compileShader( GL_FRAGMENT_SHADER, fragmentShaderSource );
  glAttachShader( pid, vsId );
  glAttachShader( pid, fsId );
  glLinkProgram( pid );

  int  result;
  char infoLog[ 512 ];
  glGetProgramiv( pid, GL_LINK_STATUS, &result );
  if ( result == false )
  {
    glGetProgramInfoLog( pid, 512, NULL, infoLog );
    std::cout << "Gl LINKER ERROR: " << std::endl << infoLog;
  }
  glUseProgram( pid );
  glDeleteShader( vsId );
  glDeleteShader( fsId );
  return pid;
}
unsigned int compileShader( unsigned int type, const std::string &src )
{
  unsigned int id = glCreateShader( type );
  const char * code = src.c_str();
  // std::cout<<src.c_str();
  glShaderSource( id, 1, &code, NULL );
  glCompileShader( id );
  // error checking
  int  result;
  char infoLog[ 512 ];
  glGetShaderiv( id, GL_COMPILE_STATUS, &result );
  if ( result == false )
  {
    glGetShaderInfoLog( id, 512, NULL, infoLog );
    std::cout << "SHADER COMPILE ERROR: " << std::endl << infoLog;
  }
  return id;
}

std::string parseShader( const std::string &filepath )
{
  std::string       line;
  std::stringstream ss;
  std::ifstream     streamSh;  // input stream
  streamSh.open( filepath );   // check for faliure
  if ( !streamSh )
  {
    std::cout << "\n XERROR: failed to open shader file: \n"
              << "try running the exe from it's own directory\n"
              << "as the shaders are loaded (compiled and linked) at run \n";
  }
  while ( getline( streamSh, line ) )  // takes line by like data (end of line)
                                       // from stream and put it into line
  { ss << line << "\n"; }
  return ss.str();
}



std::string ProjDir()
{  // This is Deadly Inefficeient, but does not contribute
  std::string filePath = __FILE__;
  std::string tr( "\\" );
  std::string th( "\/" );
  int         ls{0};
  size_t      pos{0};
  // For loop for windows repalce path
  for ( auto i{0}; i < filePath.length(); i++ )
  {
    pos = filePath.find( tr );
    if ( pos == std::string::npos ) { break; }
    filePath.replace( pos, tr.length(), "\/" );
  }

  // remove from second last directory
  for ( auto j{0}; j < 2; j++ )
  {
    for ( auto i{0}; i < filePath.length(); i++ )
    {
      pos = filePath.find( th, pos + 1 );
      if ( pos != std::string::npos ) { ls = pos; }
      if ( pos == std::string::npos )
      {
        filePath.erase( ls );
        break;
      }
    }
  }
  return filePath;
}
