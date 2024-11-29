cmake_minimum_required(VERSION 3.21)
project(BaseOrrery)

set(CMAKE_CXX_STANDARD 17)
set(CMAKE_AUTOMOC ON)
set(CMAKE_AUTORCC ON)
set(CMAKE_AUTOUIC ON)

set(CMAKE_PREFIX_PATH "/Users/jonsalenger/Qt/6.2.3/macos/lib/cmake")

find_package(Qt6 COMPONENTS
        Core
        Gui
        Widgets
        REQUIRED)

add_executable(BaseOrrery main.cpp WindowWidget.cpp WindowWidget.h Celestial.cpp Celestial.h)
target_link_libraries(BaseOrrery
        Qt::Core
        Qt::Gui
        Qt::Widgets
        )

