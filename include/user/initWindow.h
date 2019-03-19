
#pragma once
//#include "user/glContextData.h"
#include <glad/glad.h>
#include <glfw/glfw3.h>
#include <iostream>



namespace windowData
{
  const int oglMajor = 4;
  const int oglMinor = 4;
  const int scWid = 600;
  const int scHei = 800;
} 


void initWinGlfw();
void test(GLFWwindow* win);
