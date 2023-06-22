cmake_minimum_required(VERSION 3.19)

project(QmlIcons VERSION 1.0 LANGUAGES CXX)

set(CMAKE_AUTOMOC ON)
set(CMAKE_AUTORCC ON)

find_package(Qt6 COMPONENTS Core Gui Qml Quick QuickControls2 REQUIRED)

qt_add_executable(qmlicons WIN32
    main.cpp
)

qt_add_qml_module(qmlicons
    URI QmlIcons
    VERSION 1.0
    SOURCES
        iconloader.h
    QML_FILES
        main.qml
    NO_RESOURCE_TARGET_PATH
)

target_include_directories(qmlicons PUBLIC "${PROJECT_SOURCE_DIR}/..")

qt_add_resources(qmlicons "qmlicons_icons"
    PREFIX
        "/QmlIcons"
    FILES
        icons/codepoints.json
        icons/MaterialIcons-Regular.ttf
)

set_target_properties(qmlicons PROPERTIES
    CXX_STANDARD              17
    CXX_STANDARD_REQUIRED     YES
    CXX_EXTENSIONS            NO
)

target_compile_definitions(qmlicons
    PRIVATE $<$<OR:$<CONFIG:Debug>,$<CONFIG:RelWithDebInfo>>:QT_QML_DEBUG>)

target_link_libraries(qmlicons
    PRIVATE
        Qt::Core
        Qt::Gui
        Qt::Qml
        Qt::Quick
        Qt::QuickControls2
)
