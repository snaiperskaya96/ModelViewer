cmake_minimum_required(VERSION 3.6)
project(ModelViewer)

set(CMAKE_CXX_STANDARD 11)
set(CMAKE_MODULE_PATH ${CMAKE_MODULE_PATH} "${CMAKE_SOURCE_DIR}/cmake/Modules/")

find_package(GLFW REQUIRED)
find_package(GLEW REQUIRED)
find_package(OpenGL REQUIRED)

add_subdirectory(deps/tetgen)

set(SOURCE_FILES src/main.cpp src/Tools/Shaders/ShaderBuilder.cpp src/Tools/Shaders/ShaderBuilder.h src/Tools/Misc/FrameRate.cpp src/Tools/Misc/FrameRate.h src/Tools/Misc/Debug.cpp src/Tools/Misc/Debug.h src/Tools/OpenGl/OpenGl.cpp src/Tools/OpenGl/OpenGl.h src/Tools/Math/Math.cpp src/Tools/Math/Math.h src/Tools/Math/Vector3.h src/Tools/Math/Vector4.h src/Tools/Math/Matrix3.h src/Tools/Math/Matrix4.h src/Actors/Camera.cpp src/Actors/Camera.h src/Actors/Actor.cpp src/Actors/Actor.h src/ModelViewer.h src/Actors/TestActor.cpp src/Actors/TestActor.h src/Components/MeshComponent.cpp src/Components/MeshComponent.h src/Tools/Mesh/ObjImporter.cpp src/Tools/Mesh/ObjImporter.h)
add_executable(ModelViewer ${SOURCE_FILES})

include_directories(${GLFW_INCLUDE_DIR} ${GLEW_INCLUDE_DIR} ${OPENGL_INCLUDE_DIR} src/ src/Tools deps/tetgen)
target_link_libraries(ModelViewer ${GLFW_LIBRARIES} ${GLEW_LIBRARY} ${OPENGL_LIBRARIES} tet)

file(COPY extra/Shaders DESTINATION ${PROJECT_BINARY_DIR}/)
file(COPY extra/ObjMeshes DESTINATION ${PROJECT_BINARY_DIR}/)
