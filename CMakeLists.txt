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


set(CMAKE_AUTOUIC ON)
set(CMAKE_AUTOMOC ON)
set(CMAKE_AUTORCC ON)

set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_STANDARD_REQUIRED ON)

find_package(QT NAMES Qt6 Qt5 REQUIRED COMPONENTS Widgets)
find_package(Qt${QT_VERSION_MAJOR} REQUIRED COMPONENTS Widgets)
find_package(fmt REQUIRED)
find_package(nlohmann_json CONFIG REQUIRED)
find_package(Xlnt CONFIG REQUIRED)

# ---- Declare executable ----

set(PROJECT_SOURCES
    source/main.cpp
    source/network_interaction.cpp
    source/carbon_sink_exporter.cpp
    source/carbon_sink_form.cpp
    source/mainwindow.cpp
    source/mainwindow.ui
    source/pca_model.cpp
    source/page_login.cpp
    source/page_login.ui
    source/page_input_param.cpp
    source/page_input_param.ui
)



if(${QT_VERSION_MAJOR} GREATER_EQUAL 6)
    qt_add_resources(
        ui_style
        ${CMAKE_CURRENT_SOURCE_DIR}/style/app.qrc
    )
    qt_add_executable(carbon-sink-calculation
        MANUAL_FINALIZATION
        ${PROJECT_SOURCES}
        ${ui_style}

    )
# Define target properties for Android with Qt 6 as:
#    set_property(TARGET carbon-sink-calculation APPEND PROPERTY QT_ANDROID_PACKAGE_SOURCE_DIR
#                 ${CMAKE_CURRENT_SOURCE_DIR}/android)
# For more information, see https://doc.qt.io/qt-6/qt-add-executable.html#target-creation
else()
    qt5_add_resources(
      ui_style
      ${CMAKE_CURRENT_SOURCE_DIR}/style/app.qrc
    )

    if(ANDROID)
        add_library(carbon-sink-calculation SHARED
            ${PROJECT_SOURCES}
            ${ui_style}
        )
# Define properties for Android with Qt 5 after find_package() calls as:
#    set(ANDROID_PACKAGE_SOURCE_DIR "${CMAKE_CURRENT_SOURCE_DIR}/android")
    else()
        add_executable(carbon-sink-calculation
            ${PROJECT_SOURCES}
            ${ui_style}
        )
    endif()
endif()

set_property(TARGET carbon-sink-calculation PROPERTY OUTPUT_NAME carbon-sink-calculation)

target_compile_features(carbon-sink-calculation PRIVATE cxx_std_20)

target_link_libraries(carbon-sink-calculation
    PRIVATE
    Qt${QT_VERSION_MAJOR}::Widgets
    nlohmann_json::nlohmann_json
    xlnt::xlnt
  )

# Qt for iOS sets MACOSX_BUNDLE_GUI_IDENTIFIER automatically since Qt 6.1.
# If you are developing for iOS or macOS you should consider setting an
# explicit, fixed bundle identifier manually though.
if(${QT_VERSION} VERSION_LESS 6.1.0)
  set(BUNDLE_ID_OPTION MACOSX_BUNDLE_GUI_IDENTIFIER com.example.carbon-sink-calculation)
endif()
set_target_properties(carbon-sink-calculation PROPERTIES
    ${BUNDLE_ID_OPTION}
    MACOSX_BUNDLE_BUNDLE_VERSION ${PROJECT_VERSION}
    MACOSX_BUNDLE_SHORT_VERSION_STRING ${PROJECT_VERSION_MAJOR}.${PROJECT_VERSION_MINOR}
    MACOSX_BUNDLE TRUE
    WIN32_EXECUTABLE TRUE
)

include(GNUInstallDirs)
install(TARGETS carbon-sink-calculation
    BUNDLE DESTINATION .
    LIBRARY DESTINATION ${CMAKE_INSTALL_LIBDIR}
    RUNTIME DESTINATION ${CMAKE_INSTALL_BINDIR}
)

if(QT_VERSION_MAJOR EQUAL 6)
    qt_finalize_executable(carbon-sink-calculation)
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
