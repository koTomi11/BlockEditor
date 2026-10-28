# CMakeList.txt : CMake project for W3Deditor, include source and define
# project specific logic here.
#
cmake_minimum_required (VERSION 3.10)

include(FetchContent)
FetchContent_Declare(
    glfw
    GIT_REPOSITORY https://github.com/glfw/glfw.git
    GIT_TAG        3.4 # Vagy az aktuális legfrissebb verzió
)

FetchContent_Declare(
    glad
    GIT_REPOSITORY https://github.com/Dav1dde/glad.git
    GIT_TAG        v0.1.36 # A stabil v0 verzió kiválóan beépül a CMake-be
)

# Itt megadjuk a GLAD konfigurációját, mielőtt beolvassuk
set(GLAD_GL_VERSION "4.6" CACHE STRING "" FORCE)
set(GLAD_PROFILE "core" CACHE STRING "OpenGL profile")
set(GLAD_GENERATOR "c" CACHE STRING "Language to generate binding")

FetchContent_GetProperties(glad)
if(NOT glad_POPULATED)
    FetchContent_Populate(glad)
    # Az EXCLUDE_FROM_ALL biztosítja, hogy csak azt fordítsa le, amit tényleg használunk
    add_subdirectory(${glad_SOURCE_DIR} ${glad_BINARY_DIR} EXCLUDE_FROM_ALL)
endif()

FetchContent_GetProperties(glfw)
if(NOT glfw_POPULATED)
    FetchContent_Populate(glfw)
    add_subdirectory(${glfw_SOURCE_DIR} ${glfw_BINARY_DIR})
endif()

add_executable(W3Deditor src/main.cpp src/Render.h src/Render.cpp)

target_include_directories(W3Deditor PRIVATE ${glfw_SOURCE_DIR}/include
											 ${glad_SOURCE_DIR}/include)

# 3. Összelinkeljük a programot a GLFW könyvtárral
target_link_libraries(W3Deditor PRIVATE glfw glad)


