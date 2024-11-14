cmake_minimum_required(VERSION 3.16)

project(zip-viewer-app VERSION 0.1 LANGUAGES CXX)

set(CMAKE_AUTOUIC ON)
set(CMAKE_AUTOMOC ON)
set(CMAKE_AUTORCC ON)

set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_STANDARD_REQUIRED ON)

find_package(QT NAMES Qt6 Qt5 REQUIRED COMPONENTS Widgets)
find_package(Qt6 REQUIRED COMPONENTS Widgets)
find_package(Qt6 REQUIRED COMPONENTS Gui)
set(PROJECT_SOURCES main.cpp mainwindow.h mainwindow.cpp clickable_label.h table_view_model.h table_view_model.cpp minizip_read_list.cpp)

execute_process(COMMAND git clone https://github.com/zlib-ng/minizip-ng.git
                WORKING_DIRECTORY ${CMAKE_SOURCE_DIR})

execute_process(COMMAND cmake -S . -B build -D MZ_COMPAT=OFF -D MZ_ZLIB=OFF -D MZ_BZIP2=OFF -D MZ_LZMA=OFF -D MZ_ZSTD=OFF -D MZ_LIBCOMP=OFF -D MZ_PKCRYPT=OFF -D MZ_WZAES=OFF -D MZ_ICONV=OFF
                WORKING_DIRECTORY ${CMAKE_SOURCE_DIR}/minizip-ng)

execute_process(COMMAND cmake --build build --config RELEASE
                WORKING_DIRECTORY ${CMAKE_SOURCE_DIR}/minizip-ng)

include_directories(minizip-ng)

add_executable(${PROJECT_NAME} ${PROJECT_SOURCES})

set(STATIC_LIB_EXTENSION)

if(WIN32)
# Gryab: annoying windows console
 set_property(TARGET ${PROJECT_NAME} PROPERTY WIN32_EXECUTABLE true)
# Gryab: minizip-ng doesn't throw cpp exceptions, otherwise default
 target_compile_options(${PROJECT_NAME} PUBLIC "/EHsc")
# Gryab: cl tries to open .obj instead of static lib
 set(STATIC_LIB_EXTENSION ".lib")
 target_compile_options(${PROJECT_NAME} PUBLIC "/DWIN32")
else()
 set(STATIC_LIB_EXTENSION ".a")
endif()

target_link_libraries(${PROJECT_NAME} PRIVATE ${CMAKE_SOURCE_DIR}/minizip-ng/build/Release/minizip-ng${STATIC_LIB_EXTENSION})
target_link_libraries(${PROJECT_NAME} PRIVATE Qt6::Widgets)
target_link_libraries(${PROJECT_NAME} PRIVATE Qt6::Gui)
