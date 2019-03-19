// OpenGlTest.cpp : This file contains the 'main' function. Program execution
// begins and ends there. https://learnopengl.com link to some tutorial
// using clang format
#include "user/data.h"
#include <cassert>
#include <fstream>
#include <glad/glad.h>
#include <glfw/glfw3.h>
#include <iostream>
#include <sstream>
#include <string>

void fb_sz_cb(GLFWwindow *window, int width, int height);
void key_cb(GLFWwindow *window, int key, int scancode, int action, int mods);
unsigned int compileShader(unsigned int type, const std::string &src);
unsigned int createProgram(const std::string &vertex_shaderSource,
                           const std::string &fragment_shaderSource);
static std::string parseShader(const std::string &filepath);

//-----START MAIN----//
int main() {
  /*
  std::cout<<__FILE__;
  
  std::string file_path = __FILE__;
  std::string dir_path = file_path.substr(0, file_path.rfind("\\"));
  std::cout << dir_path << std::endl;
  std::cout<<"hahahahahahah ";
  dir_path.erase(dir_path.end() - 3, dir_path.end()); // more hackey than i like
  std::cout << dir_path;
  */
  assert(sizeof(GLuint) == sizeof(unsigned int));
  // printf("OpenGL version supported by this platform (%s): \n",
  // glGetString(GL_VERSION));CREATE A SEGMENTATION FAULT

#pragma region createWindow
  if (!glfwInit()) {
    std::cout << "GLFW failed initialization";
    return -1;
  } // initialize glfw
  glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 4);
  glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 4);
  glfwWindowHint(GLFW_OPENGL_PROFILE, GLFW_OPENGL_CORE_PROFILE);
  GLFWwindow *window =
      glfwCreateWindow(800, 640, "hey", 0, 0); // glfw window creation
  if (!window) {
    std::cout << "window creation failed nigga";
  } // check for window creation
  glfwMakeContextCurrent(window);
  if (!gladLoadGLLoader((GLADloadproc)glfwGetProcAddress)) {
    std::cout << "glad load failed";
  } // initialize glad
  glfwSetFramebufferSizeCallback(window, fb_sz_cb);
#pragma endregion

  // SHADER STUFF
  std::string vertex_shader_source =
      parseShader( "../res/shaders/shader.vert");
  std::string fragment_shader_source =
      parseShader("../res/shaders/shader.frag");
  unsigned int shaderProgram =
      createProgram(vertex_shader_source, fragment_shader_source);

  std::cout << glGetString(GL_VERSION);
#pragma region BufferAndPass
  GLuint vbo, vao, ebo;

  glGenVertexArrays(1, &vao);
  glBindVertexArray(vao);
  //	glGenBuffers(1, &vboR);
  glGenBuffers(1, &vbo);
  glBindBuffer(GL_ARRAY_BUFFER, vbo);
  glBufferData(GL_ARRAY_BUFFER, sizeof(vertices), vertices, GL_STATIC_DRAW);

  glGenBuffers(1, &ebo);
  glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, ebo);
  glBufferData(GL_ELEMENT_ARRAY_BUFFER, sizeof(indices), indices,
               GL_STATIC_DRAW);

  // bind array data to shader
  glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 3 * sizeof(float), (void *)0);
  glEnableVertexAttribArray(0);
  glVertexAttribPointer(1, 4, GL_FLOAT, GL_FALSE, sizeof(float),
                        (void *)(12 * sizeof(float)));
  glEnableVertexAttribArray(1);
#pragma endregion

  glClearColor(0.2f, 0.3f, 0.3f, 1.0f);

  //	int f = 0;
  //	float fk = 0.05f;
  // Rendering Loop
  while (!glfwWindowShouldClose(window)) {
    glfwSetKeyCallback(window, key_cb);
    glClear(GL_COLOR_BUFFER_BIT);
    glDrawElements(GL_TRIANGLES, 6, GL_UNSIGNED_INT, 0);
    glfwSwapBuffers(window);
    glfwPollEvents();
  }
  glDeleteProgram(shaderProgram);
  glfwTerminate();
  return 0;
}
//-----END MAIN-----//

void key_cb(GLFWwindow *window, int key, int scancode, int action, int mods) {
  if (key == GLFW_KEY_ESCAPE && action == GLFW_PRESS) {
    glfwSetWindowShouldClose(window, 1);
  }
}

void fb_sz_cb(GLFWwindow *window, int width, int height) {
  glViewport(0, 0, width, height);
}
unsigned int compileShader(unsigned int type, const std::string &src) {
  unsigned int id = glCreateShader(type);
  const char *code = src.c_str();
  glShaderSource(id, 1, &code, NULL);
  glCompileShader(id);
  int result;
  char infoLog[512];

  glGetShaderiv(id, GL_COMPILE_STATUS, &result);
  if (result == GL_FALSE) {
    glGetShaderInfoLog(id, 512, NULL, infoLog);
    std::cout << "COMPILE ERROR::" << std::endl << infoLog;
  }

  return id;
}
unsigned int createProgram(const std::string &vertex_shaderSource,
                           const std::string &fragment_shaderSource) {
  unsigned int pid = glCreateProgram();
  unsigned int vs = compileShader(GL_VERTEX_SHADER, vertex_shaderSource);
  unsigned int fs = compileShader(GL_FRAGMENT_SHADER, fragment_shaderSource);
  glAttachShader(pid, vs);
  glAttachShader(pid, fs);
  glLinkProgram(pid);
  int result;
  char infoLog[512];
  glGetProgramiv(pid, GL_LINK_STATUS, &result);
  if (result == GL_FALSE) {
    glGetProgramInfoLog(pid, 512, NULL, infoLog);
    std::cout << "LINK ERROR::" << std::endl << infoLog;
  }
  glUseProgram(pid);
  glDeleteShader(vs);
  glDeleteShader(fs);
  return pid;
}
static std::string parseShader(const std::string &filepath) {
  std::ifstream stream(filepath);
  std::string line;
  std::stringstream ss;
  while (getline(stream, line)) {
    if (line.find("#version") != std::string::npos) {
      // std::cout << "hey";
    }
    ss << line << "\n";
  }
  return ss.str();
}

/*



*/
