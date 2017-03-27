cmake_minimum_required(VERSION 3.6)
project(ModelViewer)

set(CMAKE_CXX_STANDARD 11)
set(CMAKE_MODULE_PATH ${CMAKE_MODULE_PATH} "${CMAKE_SOURCE_DIR}/cmake/Modules/")

find_package(GLFW REQUIRED)
find_package(GLEW REQUIRED)
find_package(OpenGL REQUIRED)

set(SOURCE_FILES main.cpp src/Tools/Shaders/ShaderBuilder.cpp src/Tools/Shaders/ShaderBuilder.h src/Tools/Misc/FrameRate.cpp src/Tools/Misc/FrameRate.h src/Tools/Misc/Debug.cpp src/Tools/Misc/Debug.h src/Tools/OpenGl/OpenGl.cpp src/Tools/OpenGl/OpenGl.h)
add_executable(ModelViewer ${SOURCE_FILES})

include_directories(${GLFW_INCLUDE_DIR} ${GLEW_INCLUDE_DIR} ${OPENGL_INCLUDE_DIR} src/Tools)
target_link_libraries(ModelViewer ${GLFW_LIBRARIES} ${GLEW_LIBRARY} ${OPENGL_LIBRARIES} -lglew32 -lglfw3 -lopengl32)
