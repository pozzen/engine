cmake_minimum_required(VERSION 2.8)

project(StotEngine)

add_definitions("-std=c++11")
file(GLOB_RECURSE sources Source/**.cpp Source/**.h)
add_executable(${PROJECT_NAME} ${sources})

# Build static version of Assimp
#SET(ASSIMP_BUILD_STATIC_LIB ON CACHE BOOL "")

#include(ExternalProject)
#ExternalProject_Add(Assimp SOURCE_DIR ${CMAKE_SOURCE_DIR}/ThirdParty/assimp-3.1.1/ INSTALL_DIR ./assimp-3.1.1/build)
#add_subdirectory(./ThirdParty/assimp-3.1.1/)

if(NOT CMAKE_CROSSCOMPILING)
	INCLUDE(FindPkgConfig)
	PKG_SEARCH_MODULE(SDL2 REQUIRED sdl2)
	PKG_SEARCH_MODULE(GLEW REQUIRED glew)
	PKG_SEARCH_MODULE(TINYXML2 REQUIRED tinyxml2)
	FIND_PACKAGE(OpenGL REQUIRED)
	FIND_PACKAGE(assimp REQUIRED)
	FIND_PACKAGE(Bullet REQUIRED)

	INCLUDE_DIRECTORIES(Source ./ThirdParty/glm/ ${SDL2_INCLUDE_DIRS} ${OPENGL_INCLUDE_DIRS} ${GLEW_INCLUDE_DIRS} ${ASSIMP_INCLUDE_DIRS} ${BULLET_INCLUDE_DIRS} ${TINYXML2_INCLUDE_DIRS})

	TARGET_LINK_LIBRARIES(${PROJECT_NAME} ${SDL2_LIBRARIES} ${OPENGL_LIBRARIES} ${GLEW_LIBRARIES} ${ASSIMP_LIBRARIES} ${BULLET_LIBRARIES} ${TINYXML2_LIBRARIES})
elseif(CMAKE_CROSSCOMPILING)
	set_target_properties(${PROJECT_NAME} PROPERTIES LINK_FLAGS "-o index.html \
								    -s USE_SDL=2 \
								    -s TOTAL_MEMORY=33554432 \
								    --preload-file ../Assets/@Assets/")

	INCLUDE_DIRECTORIES(Source ./ThirdParty/glm/ ./ThirdParty/assimp-3.1.1/include ${SDL2_INCLUDE_DIRS})
	TARGET_LINK_LIBRARIES(${PROJECT_NAME} Assimp)
endif(NOT CMAKE_CROSSCOMPILING)

