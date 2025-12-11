project(tests)

# Включаем поддержку тестирования
enable_testing(true)

# Добавляем путь к Qt Test
find_package(Qt6 REQUIRED COMPONENTS Test)

# Создаем тестовый исполняемый файл
add_executable(model_test
        weather_model_src/main.cpp
        weather_model_src/weather_model_test.cpp
        weather_model_src/weather_model_test.hpp
)

add_test(NAME model_test COMMAND model_test)
target_include_directories(model_test PRIVATE
        ${CMAKE_CURRENT_SOURCE_DIR}/..)
target_link_libraries(model_test PRIVATE Qt6::Test model_lib)

# Создаем тестовый исполняемый файл
add_executable(repository_test
        repository_tests_src/main.cpp
        repository_tests_src/repository_test.hpp
        repository_tests_src/repository_test.cpp
)

add_test(NAME repository_test COMMAND repository_test)
target_include_directories(repository_test PRIVATE
        ${CMAKE_CURRENT_SOURCE_DIR}/..)
target_link_libraries(repository_test PRIVATE Qt6::Test Qt6::Network
        repository_lib
        model
        datasource
)

# Создаем тестовый исполняемый файл
add_executable(data_test
        weather_data_tests_src/main.cpp
        weather_data_tests_src/weather_data_test.hpp
        weather_data_tests_src/weather_data_test.cpp
)

add_test(NAME data_test COMMAND data_test)
target_include_directories(data_test PRIVATE
        ${CMAKE_CURRENT_SOURCE_DIR}/..)
target_link_libraries(data_test PRIVATE Qt6::Test Qt6::Network
        data_lib
        model
)

