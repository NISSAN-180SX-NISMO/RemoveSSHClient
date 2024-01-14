cmake_minimum_required(VERSION 3.27)
project(RemoteSSHClient)

set(CMAKE_CXX_STANDARD 17)
set(CMAKE_AUTOMOC ON)
set(CMAKE_AUTORCC ON)
set(CMAKE_AUTOUIC ON)

set(CMAKE_PREFIX_PATH "C:/QT/6.4.2/mingw_64/lib/cmake")

set(libssh_DIR vcpkg/installed/x64-windows/share/libssh/)

find_package(Qt6 COMPONENTS Core Gui Widgets REQUIRED)
find_package(libssh CONFIG REQUIRED)
message(STATUS "LIBSSH_INCLUDE_DIRS: ${LIBSSH_INCLUDE_DIRS}")
message(STATUS "LIBSSH_LIBRARIES: ${LIBSSH_LIBRARIES}")


add_executable(RemoteSSHClient main.cpp
        Controllers/SSHController/SSHController.cpp
        Controllers/SSHController/SSHController.h
        View/MainWindow/mainwindow.cpp
        View/MainWindow/mainwindow.h
        View/MainWindow/mainwindow.ui
        Model/SSHConnection/SSHConnection.cpp
        Model/SSHConnection/SSHConnection.h
        Controllers/SSHController/SSHControllerException.h
)

target_include_directories(RemoteSSHClient PRIVATE ${LIBSSH_INCLUDE_DIRS})  # Важное изменение
message(STATUS "LIBSSH_INCLUDE_DIRS: ${LIBSSH_INCLUDE_DIRS}")

target_link_libraries(RemoteSSHClient PRIVATE Qt::Core Qt::Gui Qt::Widgets ssh)  # Важное изменение

if (WIN32 AND NOT DEFINED CMAKE_TOOLCHAIN_FILE)
    set(DEBUG_SUFFIX)
    if (MSVC AND CMAKE_BUILD_TYPE MATCHES "Debug")
        set(DEBUG_SUFFIX "d")
    endif ()
    set(QT_INSTALL_PATH "${CMAKE_PREFIX_PATH}")
    if (NOT EXISTS "${QT_INSTALL_PATH}/bin")
        set(QT_INSTALL_PATH "${QT_INSTALL_PATH}/..")
        if (NOT EXISTS "${QT_INSTALL_PATH}/bin")
            set(QT_INSTALL_PATH "${QT_INSTALL_PATH}/..")
        endif ()
    endif ()
    if (EXISTS "${QT_INSTALL_PATH}/plugins/platforms/qwindows${DEBUG_SUFFIX}.dll")
        add_custom_command(TARGET ${PROJECT_NAME} POST_BUILD
                COMMAND ${CMAKE_COMMAND} -E make_directory
                "$<TARGET_FILE_DIR:${PROJECT_NAME}>/plugins/platforms/")
        add_custom_command(TARGET ${PROJECT_NAME} POST_BUILD
                COMMAND ${CMAKE_COMMAND} -E copy
                "${QT_INSTALL_PATH}/plugins/platforms/qwindows${DEBUG_SUFFIX}.dll"
                "$<TARGET_FILE_DIR:${PROJECT_NAME}>/plugins/platforms/")
    endif ()
    foreach (QT_LIB Core Gui Widgets)
        add_custom_command(TARGET ${PROJECT_NAME} POST_BUILD
                COMMAND ${CMAKE_COMMAND} -E copy
                "${QT_INSTALL_PATH}/bin/Qt6${QT_LIB}${DEBUG_SUFFIX}.dll"
                "$<TARGET_FILE_DIR:${PROJECT_NAME}>")
    endforeach (QT_LIB)
endif ()
