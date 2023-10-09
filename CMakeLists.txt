set(CMAKE_VERSION 3.20)
cmake_minimum_required(VERSION ${CMAKE_VERSION})

project("Earth_System" VERSION 0.1.0)

set(SOURCES_DIRECTORY "${CMAKE_CURRENT_LIST_DIR}/src")
set(SOURCES
  "${SOURCES_DIRECTORY}/main.cpp"
  "${SOURCES_DIRECTORY}/Asset.cpp"
  "${SOURCES_DIRECTORY}/Shader.cpp"
)

set(GLFW_DIRECTORY "${CMAKE_CURRENT_LIST_DIR}/libs/GLFW")

if (MSVC) 
  set(GLFW_IMPORTED_LOCATION "${GLFW_DIRECTORY}/glfw3.lib")
elseif (MINGW) 
  set(GLFW_IMPORTED_LOCATION "${GLFW_DIRECTORY}/libglfw3.a")
else () 
  set(GLFW_IMPORTED_LOCATION "${GLFW_DIRECTORY}/libglfw3.a")
endif ()

if (NOT EXISTS ${GLFW_IMPORTED_LOCATION})
  message(FATAL_ERROR "${PROJECT_NAME} - GLFW not found at ${GLFW_IMPORTED_LOCATION}")
endif ()

set(GLFW_INCLUDE "${GLFW_DIRECTORY}/include")
if (NOT EXISTS "${GLFW_INCLUDE}/GLFW/glfw3.h")
  message(FATAL_ERROR "${PROJECT_NAME} - glfw.h not found at ${GLFW_INCLUDE}")
endif ()

add_library(glfw3 STATIC IMPORTED)
set_target_properties(glfw3 PROPERTIES
  IMPORTED_LOCATION ${GLFW_IMPORTED_LOCATION}
  INTERFACE_INCLUDE_DIRECTORIES ${GLFW_INCLUDE}
)
message(STATUS "${PROJECT_NAME} - GLFW3 imported as STATIC library")

set(GLAD_FOLDER "${CMAKE_CURRENT_LIST_DIR}/libs/GLAD")
set(GLAD_SOURCES "${GLAD_FOLDER}/src/gl.c")
set(GLAD_INCLUDE "${GLAD_FOLDER}/include")

set(SOURCES
  ${GLAD_SOURCES}
  ${SOURCES}
)

if (MINGW) 
  find_library(opengl "libopengl32.a")
elseif (MSVC) 
  find_library(opengl "OpenGL32.lib")
else () 
  find_library(opengl "libopengl.a")
endif ()

if (opengl)
  message(STATUS "${PROJECT_NAME} - OpenGL Library found at ${opengl}")
else ()
  message(FATAL_ERROR "${PROJECT_NAME} - OpenGL not found. Configure SDK and check packages")
endif ()

set(STB_IMAGE_INCLUDE "${CMAKE_CURRENT_LIST_DIR}/libs/stb")


add_executable(app ${SOURCES})

set_target_properties(app PROPERTIES
  RUNTIME_OUTPUT_NAME "Earth_System_v${PROJECT_VERSION}"
  RUNTIME_OUTPUT_DIRECTORY "${CMAKE_CURRENT_LIST_DIR}/bin"
)

target_link_libraries(app
  glfw3
  ${opengl}
)

target_include_directories(app PRIVATE ${GLAD_INCLUDE})

target_include_directories(app PRIVATE ${STB_IMAGE_INCLUDE})

target_include_directories(app PRIVATE ${SOURCES_DIRECTORY})

