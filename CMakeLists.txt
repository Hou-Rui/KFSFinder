cmake_minimum_required(VERSION 3.16)
project(kfsfinder LANGUAGES CXX)

set(CMAKE_EXPORT_COMPILE_COMMANDS ON)

find_package(Qt6 REQUIRED COMPONENTS Core Widgets)
find_package(KF6KIO)
qt_standard_project_setup()

add_subdirectory(src)

target_link_libraries(kfsfinder PRIVATE
    Qt::Core
    Qt::Widgets
    KF6::KIOCore
    KF6::KIOFileWidgets
    KF6::KIOWidgets
)
