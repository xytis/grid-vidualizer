cmake_minimum_required(VERSION 2.8)

project(grid_visualizer)

find_package(OpenGL REQUIRED)
find_package(GLUT REQUIRED)
include_directories( ${OPENGL_INCLUDE_DIRS}  ${GLUT_INCLUDE_DIRS} )

add_executable(grid_visualizer src/main.cpp src/CGrid.cpp)

target_link_libraries(grid_visualizer ${OPENGL_LIBRARIES} ${GLUT_LIBRARY} )

install(TARGETS grid_visualizer RUNTIME DESTINATION bin)
