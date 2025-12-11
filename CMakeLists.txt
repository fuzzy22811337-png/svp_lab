cmake_minimum_required(VERSION 4.0)
project(SiziesWeather2 LANGUAGES CXX)

set(CMAKE_CXX_STANDARD 20)
set(CMAKE_AUTOMOC ON)
set(CMAKE_AUTORCC ON)
#set(CMAKE_AUTOUIC ON)


find_package(Qt6 REQUIRED COMPONENTS
    Core
    Network
    Widgets
)

add_subdirectory(src/data/model)
add_subdirectory(src/data/datasource)
add_subdirectory(src/data/repository)
add_subdirectory(src/ui)

add_executable(SiziesWeather2 main.cpp)

target_link_libraries(${PROJECT_NAME} PRIVATE
        Qt::Core
        Qt::Network
        Qt::Widgets
        model
        datasource
        repository
        ui
)


add_subdirectory(tests)

add_library(model_lib src/data/model/weather_model.cpp
        src/data/model/weather_model.hpp)
target_link_libraries(model_lib PRIVATE Qt6::Core)


add_library(repository_lib src/data/repository/repository.cpp
        src/data/repository/repository.hpp)
target_link_libraries(repository_lib PRIVATE Qt6::Core Qt6::Network model datasource)


add_library(data_lib src/data/datasource/weather_data_source.hpp
        src/data/datasource/weather_data_source.cpp)
target_link_libraries(data_lib PRIVATE Qt6::Core Qt6::Network model datasource)


if (WIN32)
    add_custom_command(TARGET SiziesWeather2 POST_BUILD
        COMMAND ${CMAKE_COMMAND} -E make_directory
        "$<TARGET_FILE_DIR:SiziesWeather2>/plugins/tls"
        COMMAND ${CMAKE_COMMAND} -E copy
        "$<TARGET_FILE_DIR:Qt6::Network>/../plugins/tls/qschannelbackend.dll"
        "$<TARGET_FILE_DIR:SiziesWeather2>/plugins/tls/"
    )
endif()