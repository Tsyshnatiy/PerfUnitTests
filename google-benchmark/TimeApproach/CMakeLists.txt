set(EXECUTABLE_NAME "GB_TimeTests")

set(SOURCES ${CMAKE_CURRENT_LIST_DIR}/main.cpp)

add_executable(${EXECUTABLE_NAME} ${SOURCES})

set_property(TARGET ${EXECUTABLE_NAME} PROPERTY CXX_STANDARD 20)

find_package(benchmark REQUIRED)
target_include_directories(${EXECUTABLE_NAME} PUBLIC "${benchmark_INCLUDE_DIRS}")
target_link_libraries(${EXECUTABLE_NAME} benchmark::benchmark)
