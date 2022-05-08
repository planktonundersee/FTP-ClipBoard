cmake_minimum_required(VERSION 3.5)

project(FTP-ClipBoard VERSION 0.1 LANGUAGES CXX)

set(CMAKE_INCLUDE_CURRENT_DIR ON)

set(CMAKE_AUTOUIC ON)
set(CMAKE_AUTOMOC ON)
set(CMAKE_AUTORCC ON)

include_directories(F:/Programs/opencv/build/include/opencv2)

set(CMAKE_CXX_STANDARD 14)
set(CMAKE_CXX_STANDARD_REQUIRED ON)

#if (WIN32 OR MSVC)
#    set(CMAKE_FIND_LIBRARY_SUFFIXES ".lib")
#elseif (UNIX)
#    # 仅查找静态库，强制后缀为 .a
#    set(CMAKE_FIND_LIBRARY_SUFFIXES ".a")
#
#    # 如果只是优先查找静态库，保证 .a 后缀在前面即可，把默认的后缀加上
#    set(CMAKE_FIND_LIBRARY_SUFFIXES .a ${CMAKE_FIND_LIBRARY_SUFFIXES})
#endif()

find_package(QT NAMES Qt6 COMPONENTS Widgets network REQUIRED)
find_package(Qt${QT_VERSION_MAJOR} COMPONENTS Widgets network REQUIRED)

link_libraries(${PROJECT_SOURCE_DIR}/libiohook/lib/uiohook.dll)

set(PROJECT_SOURCES  main.cpp
        mainwindow/mainwindow.cpp
        mainwindow/mainwindow.ui
        mainwindow/mainwindow.h
        mainwindow/ui_mainwindow.h
        file_class/file_class.cpp
        file_class/file_class.h
        network_class/network_class.cpp
        network_class/network_class.h
        Public_Func/PubilcFunc.cpp
        libiohook/include/uiohook.h
        KeyBoard_Mouse_Hook/KeyBoard_Mouse_Hook.h
        KeyBoard_Mouse_Hook/KeyBoard_Mouse_Hook.cpp libiohook/GlobalParameter.h Public_Func/PublicFunc.h)

if (${QT_VERSION_MAJOR} GREATER_EQUAL 6)
    qt_add_executable(FTP-ClipBoard
            MANUAL_FINALIZATION
            ${PROJECT_SOURCES}
            )
    # Define target properties for Android with Qt 6 as:
    #    set_property(TARGET FTP-ClipBoard APPEND PROPERTY QT_ANDROID_PACKAGE_SOURCE_DIR
    #                 ${CMAKE_CURRENT_SOURCE_DIR}/android)
    # For more information, see https://doc.qt.io/qt-6/qt-add-executable.html#target-creation
else ()
    if (ANDROID)
        add_library(FTP-ClipBoard SHARED
                ${PROJECT_SOURCES}
                )
        # Define properties for Android with Qt 5 after find_package() calls as:
        #    set(ANDROID_PACKAGE_SOURCE_DIR "${CMAKE_CURRENT_SOURCE_DIR}/android")
    else ()
        add_executable(FTP-ClipBoard
                ${PROJECT_SOURCES}
                )
    endif ()
endif ()

target_link_libraries(FTP-ClipBoard PRIVATE Qt${QT_VERSION_MAJOR}::Widgets Qt${QT_VERSION_MAJOR}::Network)

set_target_properties(FTP-ClipBoard PROPERTIES
        MACOSX_BUNDLE_GUI_IDENTIFIER my.example.com
        MACOSX_BUNDLE_BUNDLE_VERSION ${PROJECT_VERSION}
        MACOSX_BUNDLE_SHORT_VERSION_STRING ${PROJECT_VERSION_MAJOR}.${PROJECT_VERSION_MINOR}
        MACOSX_BUNDLE TRUE
        WIN32_EXECUTABLE TRUE
        )

if (QT_VERSION_MAJOR EQUAL 6)
    qt_finalize_executable(FTP-ClipBoard)
endif ()
