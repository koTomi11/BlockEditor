# CMakeList.txt : CMake project for W3Deditor, include source and define
# project specific logic here.
#
cmake_minimum_required (VERSION 3.10)

set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_STANDARD_REQUIRED ON)
set(CMAKE_CXX_EXTENSIONS OFF)



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

FetchContent_Declare(
    glm
    GIT_REPOSITORY https://github.com/g-truc/glm.git
    GIT_TAG        master # Vagy megadhatsz fix verziót is, pl. "1.0.1"
)

set(GLAD_PROFILE "compatibility" CACHE STRING "" FORCE)
set(GLAD_API "gl=3.3" CACHE STRING "" FORCE)

# 3. Letöltjük a projekt konfigurálásakor

set(STB_IMAGE_DIR "${CMAKE_BINARY_DIR}/external/stb")

# Ha még nem létezik a fájl, a CMake letölti közvetlenül a GitHubról
if(NOT EXISTS "${STB_IMAGE_DIR}/stb_image.h")
    message(STATUS "stb_image.h letöltése a GitHubról...")
    file(DOWNLOAD 
        "raw.githubusercontent.com/nothings/stb/refs/heads/master/stb_image.h"
        "${STB_IMAGE_DIR}/stb_image.h"
        SHOW_PROGRESS
    )
endif()


# Ha még nem létezik a fájl, a CMake letölti közvetlenül a GitHubról
if(NOT EXISTS "${STB_IMAGE_DIR}/stb_truetype.h")
    message(STATUS "stb_truetype.h letöltése a GitHubról...")
    file(DOWNLOAD 
        "stb_truetypehttps://raw.githubusercontent.com/nothings/stb/refs/heads/master/stb_truetype.h"
        "${STB_IMAGE_DIR}/stb_truetype.h"
        SHOW_PROGRESS
    )
endif()


FetchContent_Populate(glm)


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

add_executable(W3Deditor src/main.cpp src/Render.h src/Render.cpp src/map_builder/MapBuilder.h src/map_builder/MapBuilder.cpp src/map_builder/MapUtil.h
	src/Shader.h src/Shader.cpp src/IRender2d.h src/Font.h src/Font.cpp
	
	src/Window.h
	src/Window.cpp
	
	src/editor/Editor.h
	src/editor/Editor.cpp
	
	src/IEventListener.h
	
	src/gui/GraphicsInterface.h
	src/gui/GraphicsInterface.cpp
	
	src/gui/GuiItem.h
	src/gui/GuiItem.cpp
	src/gui/GuiPanel.h
	src/gui/GuiPanel.cpp
	src/gui/GuiGrid.h
	src/gui/GuiGrid.cpp
	
	)
	
	source_group(editor FILES 
	src/editor/Editor.h
	src/editor/Editor.cpp)
	
	source_group(map FILES
	src/map_builder/MapBuilder.h
	src/map_builder/MapBuilder.cpp
	src/map_builder/MapUtil.h)
	
	source_group(gui FILES
	src/gui/GraphicsInterface.h
	src/gui/GraphicsInterface.cpp
	src/gui/GuiItem.h
	src/gui/GuiItem.cpp
	src/gui/GuiPanel.h
	src/gui/GuiPanel.cpp
	src/gui/GuiGrid.h
	src/gui/GuiGrid.cpp
	)
	

target_include_directories(W3Deditor PRIVATE ${glfw_SOURCE_DIR}/include
											 ${glad_SOURCE_DIR}/include)

 target_include_directories(W3Deditor PRIVATE ${STB_IMAGE_DIR})
 


# 3. Összelinkeljük a programot a GLFW könyvtárral
target_link_libraries(W3Deditor PRIVATE glfw glad)
target_include_directories(W3Deditor PRIVATE "${glm_SOURCE_DIR}")

set_target_properties(W3Deditor PROPERTIES
    VS_DEBUGGER_WORKING_DIRECTORY "${CMAKE_CURRENT_SOURCE_DIR}")
