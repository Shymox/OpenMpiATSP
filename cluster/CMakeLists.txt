cmake_minimum_required(VERSION 3.10)

# set the project name
project(Main)

include_directories(${PROJECT_SOURCE_DIR}/include)

set(SOURCES
    src/Array.cpp
    src/List.cpp
    src/main.cpp
    src/Matrix.cpp
    src/MpiHelper.cpp
)


find_package(MPI REQUIRED)
include_directories(${MPI_INCLUDE_DIR})

find_package(Curses REQUIRED)
include_directories(${CURSES_INCLUDE_DIR})


add_executable(project ${SOURCES})
target_link_libraries(project ${CURSES_LIBRARIES} ${MPI_LIBRARIES})
