cmake_minimum_required(VERSION 3.15)

project(FTP_ClipBoard VERSION 0.1 LANGUAGES CXX)

set(CMAKE_INCLUDE_CURRENT_DIR ON)
set(CMAKE_EXPORT_COMPILE_COMMANDS ON)

set(CMAKE_AUTOUIC ON)
set(CMAKE_AUTOMOC ON)
set(CMAKE_AUTORCC ON)

set(CMAKE_CXX_STANDARD 14)
set(CMAKE_CXX_STANDARD_REQUIRED ON)
set(CMAKE_PREFIX_PATH /opt/Nvme/Qt6/Qt/6.9.2/gcc_64/)
set(CMAKE_PREFIX_PATH:UNINITIALIZED /opt/Nvme/Qt6/Qt/6.9.2/gcc_64/)

find_package(QT NAMES Qt6 Qt5 COMPONENTS Widgets Network Core REQUIRED)
find_package(Qt${QT_VERSION_MAJOR} COMPONENTS Widgets Network Core REQUIRED)

include_directories(${Qt6Core_INCLUDE_DIRS}
    ${Qt6Core_PRIVATE_INCLUDE_DIRS}
)

if(WIN32)
    link_libraries(${PROJECT_SOURCE_DIR}/libiohook/lib/uiohook.dll)
endif(WIN32)

set(PROJECT_SOURCES main.cpp
        mainwindow/mainwindow.cpp
        mainwindow/mainwindow.ui
        mainwindow/mainwindow.h
        mainwindow/ui_mainwindow.h
        FileClass/FileClass.cpp
        FileClass/FileClass.h
        network_class/NetworkClass.cpp
        network_class/NetworkClass.h
        Public_Func/PubilcFunc.cpp
        Public_Func/PublicFunc.h
        KeyBoardMouseHook/KeyBoardMouseHook.h
        KeyBoardMouseHook/KeyBoardMouseHook.cpp
        libiohook/include/uiohook.h)

if(${QT_VERSION_MAJOR} GREATER_EQUAL 6)
    qt_add_executable(FTP_ClipBoard
            MANUAL_FINALIZATION
            ${PROJECT_SOURCES}
    )

else()
    if(ANDROID)
        add_library(FTP_ClipBoard SHARED
                ${PROJECT_SOURCES}
        )

    else()
        add_executable(FTP_ClipBoard
                ${PROJECT_SOURCES}
        )
    endif()
endif()

target_link_libraries(FTP_ClipBoard PRIVATE
    Qt${QT_VERSION_MAJOR}::Widgets
    Qt${QT_VERSION_MAJOR}::Network
    Qt${QT_VERSION_MAJOR}::Core)

set_target_properties(FTP_ClipBoard PROPERTIES
        MACOSX_BUNDLE_GUI_IDENTIFIER my.example.com
        MACOSX_BUNDLE_BUNDLE_VERSION ${PROJECT_VERSION}
        MACOSX_BUNDLE_SHORT_VERSION_STRING ${PROJECT_VERSION_MAJOR}.${PROJECT_VERSION_MINOR}
        MACOSX_BUNDLE TRUE
        WIN32_EXECUTABLE TRUE
)

if(QT_VERSION_MAJOR EQUAL 6)
    qt_finalize_executable(FTP_ClipBoard)
endif()
