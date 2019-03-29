cmake_minimum_required(VERSION 3.13)
project (ogl VERSION 1.1)
cmake_policy(SET CMP0076 NEW)
set(CMAKE_EXPORT_COMPILE_COMMANDS ON)

set(CMAKE_MODULE_PATH ${CMAKE_MODULE_PATH} ${CMAKE_SOURCE_DIR}/cmake)

set(gls ${CMAKE_SOURCE_DIR}/lib/)

add_executable(ogl)
target_sources(ogl PUBLIC src/main.cpp src/glad.c src/initWindow.cpp src/glProg.cpp)
target_include_directories(ogl PUBLIC include lib )
target_link_directories(ogl PUBLIC lib)
if(UNIX)
  target_link_libraries(ogl PUBLIC glfw3 X11  Xrandr Xxf86vm Xinerama Xcursor  pthread dl GL)
endif(UNIX)
#for windows need to merge
if(WIN32)
  target_link_libraries(ogl  glfw3)
endif(WIN32)

#-lGL -lXi -lm -lrt


#Find sdl2 and glm if possible; however were using glfw anyway
#find_package(GLM)
#find_package(SDL2)
#${GLM_INCLUDE_DIRS} ${SDL2_INCLUDE_DIRS}
