cmake_minimum_required(VERSION 3.14)

include(cmake/prelude.cmake)

project(
    Wallpaper_Project
    VERSION 0.1.0
    DESCRIPTION "Wallpaper Project"
    HOMEPAGE_URL "https://example.com/"
    LANGUAGES C
)

include(cmake/project-is-top-level.cmake)
include(cmake/variables.cmake)

# ---- Declare library ----

add_library(
    Wallpaper_Project_lib OBJECT
    source/lib.c
)

include(FetchContent)
set(FETCHCONTENT_QUIET NO)

# ----    Raylib    ----
set(RAYLIB_VERSION 5.0)
find_package(raylib ${RAYLIB_VERSION} QUIET)

if(NOT raylib_FOUND)
    message("RAYLIB ${RAYLIB_VERSION} NOT FOUND")
    FetchContent_Declare(
        raylib
        DOWNLOAD_EXTRACT_TIMESTAMP OFF
        URL https://www.github.com/raysan5/raylib/archive/refs/tags/${RAYLIB_VERSION}.tar.gz)
endif()

if (NOT raylib_POPULATED)
    FetchContent_Populate(raylib)
    FetchCOntent_MakeAvailable(raylib)

    set(BUILD_EXAMPLES OFF CACHE BOOL "" FORCE)
    set(BUILD_STATIC ON CACHE BOOL "" FORCE)

    add_subdirectory(${raylib_SOURCE_DIR} ${raylib_BINARY_DIR})
endif()

# ---- X11 ----
find_package(X11 REQUIRED)
include_directories(${X11_INCLUDE_DIR})

find_package(Lua REQUIRED)
include_directories(/usr/local/include ${LUA_INCLUDE_DIR})

target_include_directories(
    Wallpaper_Project_lib ${warning_guard}
    PUBLIC
    "$<BUILD_INTERFACE:${PROJECT_SOURCE_DIR}/source>"
)

target_compile_features(Wallpaper_Project_lib PUBLIC c_std_99)

# ---- Declare executable ----

add_executable(Wallpaper_Project_exe source/main.c source/x11func.c source/engine.c)
add_executable(Wallpaper_Project::exe ALIAS Wallpaper_Project_exe)

set_property(TARGET Wallpaper_Project_exe PROPERTY OUTPUT_NAME Wallpaper_Project)

target_compile_features(Wallpaper_Project_exe PRIVATE c_std_99)

target_link_libraries(Wallpaper_Project_exe PRIVATE Wallpaper_Project_lib)
target_link_libraries(Wallpaper_Project_exe PRIVATE raylib)
target_link_libraries(Wallpaper_Project_exe PRIVATE ${X11_LIBRARIES})
target_link_libraries(Wallpaper_Project_exe PRIVATE ${LUA_LIBRARIES})

# ---- Copy res ----

set(RESOURCES_SRC_DIR "${CMAKE_CURRENT_SOURCE_DIR}/res")
set(RESOURCES_DST_DIR "${CMAKE_CURRENT_BINARY_DIR}")
file(MAKE_DIRECTORY ${RESOURCES_DST_DIR})
file(COPY ${RESOURCES_SRC_DIR} DESTINATION ${RESOURCES_DST_DIR})

# ---- Copy Lua ----

set(LUA_SRC_DIR "${CMAKE_CURRENT_SOURCE_DIR}/lua")
set(LUA_DST_DIR "${CMAKE_CURRENT_BINARY_DIR}")
file(MAKE_DIRECTORY ${LUA_DST_DIR})
file(COPY ${LUA_SRC_DIR} DESTINATION
${LUA_DST_DIR})



# ---- Install rules ----

if(NOT CMAKE_SKIP_INSTALL_RULES)
  include(cmake/install-rules.cmake)
endif()

# ---- Developer mode ----

if(NOT Wallpaper_Project_DEVELOPER_MODE)
  return()
elseif(NOT PROJECT_IS_TOP_LEVEL)
  message(
      AUTHOR_WARNING
      "Developer mode is intended for developers of Wallpaper_Project"
  )
endif()



include(cmake/dev-mode.cmake)
