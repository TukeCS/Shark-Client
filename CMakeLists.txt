cmake_minimum_required(VERSION 3.25)
project(InternalClient)

set(CMAKE_CXX_STANDARD 23)
set(CMAKE_CXX_STANDARD_REQUIRED ON)
set(CMAKE_POSITION_INDEPENDENT_CODE ON) # Needed for DLL

# Release / Debug flags
set(CMAKE_CXX_FLAGS_RELEASE "/O2")
set(CMAKE_CXX_FLAGS_DEBUG "/Wall /W4 /Zi")

# =====================
# ImGui
# =====================
set(IMGUI_DIR ${CMAKE_SOURCE_DIR}/api/imgui)
set(IMGUI_SOURCES
    ${IMGUI_DIR}/imgui.cpp
    ${IMGUI_DIR}/imgui_demo.cpp
    ${IMGUI_DIR}/imgui_draw.cpp
    ${IMGUI_DIR}/imgui_tables.cpp
    ${IMGUI_DIR}/imgui_widgets.cpp
    ${IMGUI_DIR}/imgui_stdlib.cpp
    ${IMGUI_DIR}/imgui_impl_opengl2.cpp
    ${IMGUI_DIR}/imgui_impl_win32.cpp
)

# =====================
# Kiero + MinHook
# =====================
set(KIERO_DIR ${CMAKE_SOURCE_DIR}/api/kiero)
set(MINHOOK_DIR ${KIERO_DIR}/minhook)

file(GLOB_RECURSE KIERO_SOURCES
    ${KIERO_DIR}/*.cpp
    ${MINHOOK_DIR}/src/*.c
    ${MINHOOK_DIR}/src/hde/*.c
)

# =====================
# Your source files
# =====================
file(GLOB_RECURSE SRC_FILES
    ${CMAKE_SOURCE_DIR}/src/*.cpp
)

# =====================
# DLL Target
# =====================
add_library(${PROJECT_NAME} SHARED
    ${SRC_FILES}
    ${IMGUI_SOURCES}
    ${KIERO_SOURCES}
)

# =====================
# Include directories
# =====================
target_include_directories(${PROJECT_NAME} PRIVATE
    ${IMGUI_DIR}
    ${KIERO_DIR}
    ${MINHOOK_DIR}/include
    ${MINHOOK_DIR}/src
    ${MINHOOK_DIR}/src/hde
    ${CMAKE_SOURCE_DIR}/src
)

# =====================
# Link libraries
# =====================
find_package(OpenGL REQUIRED)
target_link_libraries(${PROJECT_NAME} PRIVATE OpenGL32)

# Optional: link additional libraries if needed
# target_link_libraries(${PROJECT_NAME} PRIVATE winmm gdi32) # for ImGui / Windows
