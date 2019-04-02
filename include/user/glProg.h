
#pragma once
#include<string>
unsigned int       compileShader( unsigned int type, const std::string &src );
unsigned int       createProgram( const std::string &vertextShaderSource,
                                  const std::string &fragmentShaderSource );
std::string parseShader( const std::string &filepath );
std::string        ProjDir();


