project(GB_PerfUnitTests VERSION 1.0)

set(SOURCES ${CMAKE_CURRENT_LIST_DIR}/main.cpp)

add_executable(${PROJECT_NAME} ${SOURCES})

set_property(TARGET ${PROJECT_NAME} PROPERTY CXX_STANDARD 20)


find_package(benchmark REQUIRED)
target_include_directories(${PROJECT_NAME} PUBLIC "${benchmark_INCLUDE_DIRS}")
target_link_libraries(${PROJECT_NAME} benchmark::benchmark)
