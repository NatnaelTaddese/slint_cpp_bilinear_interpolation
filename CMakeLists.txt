cmake_minimum_required(VERSION 3.21)
project(my_application LANGUAGES CXX)

find_package(Slint QUIET)

if (NOT Slint_FOUND)
  message("Slint could not be located in the CMake module search path. Downloading it from Git and building it locally")
  include(FetchContent)
  FetchContent_Declare(
    Slint
    GIT_REPOSITORY https://github.com/slint-ui/slint.git
    # `release/1` will auto-upgrade to the latest Slint >= 1.0.0 and < 2.0.0
    # `release/1.0` will auto-upgrade to the latest Slint >= 1.0.0 and < 1.1.0
    GIT_TAG release/1
    SOURCE_SUBDIR api/cpp
  )
  FetchContent_MakeAvailable(Slint)
endif (NOT Slint_FOUND)


# Find OpenCV
find_package(OpenCV REQUIRED)

# Find GTK and set sources based on platform
if (WIN32)
    set(SOURCES src/main.cpp)
else()
    find_package(PkgConfig REQUIRED)
    pkg_check_modules(GTK3 REQUIRED gtk+-3.0)
    include_directories(${GTK3_INCLUDE_DIRS})
    link_directories(${GTK3_LIBRARY_DIRS})
    set(SOURCES src/main.cpp)
endif()

# Add the executable
add_executable(my_application ${SOURCES})
target_link_libraries(my_application PRIVATE Slint::Slint ${OpenCV_LIBS} ${GTK3_LIBRARIES})
target_include_directories(my_application PRIVATE ${GTK3_INCLUDE_DIRS})
target_compile_options(my_application PRIVATE ${GTK3_CFLAGS_OTHER})
slint_target_sources(my_application ui/appwindow.slint)

# On Windows, copy the Slint DLL next to the application binary so that it's found.
if (WIN32)
    add_custom_command(TARGET my_application POST_BUILD COMMAND ${CMAKE_COMMAND} -E copy $<TARGET_RUNTIME_DLLS:my_application> $<TARGET_FILE_DIR:my_application> COMMAND_EXPAND_LISTS)
endif()
