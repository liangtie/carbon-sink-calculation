cmake_minimum_required(VERSION 3.14)

include(cmake/prelude.cmake)

project(
    carbon-sink-calculation
    VERSION 0.1.0
    DESCRIPTION "Short description"
    HOMEPAGE_URL "https://example.com/"
    LANGUAGES CXX
)

include(cmake/project-is-top-level.cmake)
include(cmake/variables.cmake)

# ---- Declare library ----

add_library(
    carbon-sink-calculation_lib OBJECT
    source/lib.cpp
)

target_include_directories(
    carbon-sink-calculation_lib ${warning_guard}
    PUBLIC
    "$<BUILD_INTERFACE:${PROJECT_SOURCE_DIR}/source>"
)

target_compile_features(carbon-sink-calculation_lib PUBLIC cxx_std_20)

find_package(fmt REQUIRED)
target_link_libraries(carbon-sink-calculation_lib PRIVATE fmt::fmt)

# ---- Declare executable ----

add_executable(carbon-sink-calculation_exe source/main.cpp)
add_executable(carbon-sink-calculation::exe ALIAS carbon-sink-calculation_exe)

set_property(TARGET carbon-sink-calculation_exe PROPERTY OUTPUT_NAME carbon-sink-calculation)

target_compile_features(carbon-sink-calculation_exe PRIVATE cxx_std_20)

target_link_libraries(carbon-sink-calculation_exe PRIVATE carbon-sink-calculation_lib)

# ---- Install rules ----

if(NOT CMAKE_SKIP_INSTALL_RULES)
  include(cmake/install-rules.cmake)
endif()

# ---- Developer mode ----

if(NOT carbon-sink-calculation_DEVELOPER_MODE)
  return()
elseif(NOT PROJECT_IS_TOP_LEVEL)
  message(
      AUTHOR_WARNING
      "Developer mode is intended for developers of carbon-sink-calculation"
  )
endif()

include(cmake/dev-mode.cmake)
