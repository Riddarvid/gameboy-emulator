cmake_minimum_required ( VERSION 3.0.2 )

project ( labhelper )

# External libraries which need to be built.
add_subdirectory ( ${CMAKE_SOURCE_DIR}/external_src/imgui-1.51 ${CMAKE_CURRENT_BINARY_DIR}/imgui )
set_target_properties(imgui PROPERTIES FOLDER external)

set(glm_DIR "${CMAKE_SOURCE_DIR}/external/glm")
set(OpenGL_GL_PREFERENCE "GLVND")

find_package ( SDL2 REQUIRED )

message("> lib=${SDL2_LIBRARY} # libs=${SDL2_LIBRARIES}")
message("> dir=${SDL2_INCLUDE_DIR} # dirs=${SDL2_INCLUDE_DIRS}")

find_package ( glm REQUIRED )
find_package ( GLEW REQUIRED )
find_package ( OpenGL REQUIRED )

# Build and link library.
add_library ( labhelper 
    labhelper.h 
    labhelper.cpp 
    Model.h
    Model.cpp
    imgui_impl_sdl_gl3.h
    imgui_impl_sdl_gl3.cpp
    fbo.cpp
	fbo.h
    hdr.cpp
	hdr.h
    )

if (MSVC)
	string(REPLACE "/Od" "/O2" CMAKE_CXX_FLAGS_DEBUG_MODEL "${CMAKE_CXX_FLAGS_DEBUG_MODEL}")
	string(REPLACE "/RTC1" "" CMAKE_CXX_FLAGS_DEBUG "${CMAKE_CXX_FLAGS_DEBUG}")
else()
	set(CMAKE_CXX_FLAGS_DEBUG_MODEL "-O3")
endif()
set_property(SOURCE Model.cpp labhelper.cpp PROPERTY COMPILE_OPTIONS "$<$<CONFIG:Debug>:${CMAKE_CXX_FLAGS_DEBUG_MODEL}>")

target_include_directories( labhelper
    PUBLIC
    ${CMAKE_SOURCE_DIR}/labhelper
    ${CMAKE_SOURCE_DIR}/external_src/stb-master
    ${CMAKE_SOURCE_DIR}/external_src/tinyobjloader-1.0.6
    ${SDL2_INCLUDE_DIRS}
    ${GLM_INCLUDE_DIRS}
    ${GLEW_INCLUDE_DIRS}
    ${OPENGL_INCLUDE_DIR}
    )

#If exists SDL_LIBRARY is due to Isak having problem with SDL2::SDL2 but SDL_2LIBRARIES is working.
#/Isak


target_link_libraries ( labhelper
    PUBLIC
    imgui
	SDL2::SDL2
    ${SDL2_LIBRARIES}
    ${GLEW_LIBRARIES}
    ${OPENGL_LIBRARY}
    )
