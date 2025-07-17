cmake_minimum_required(VERSION 3.12)

set(ProjectName StackString)

project(${ProjectName})

include_directories(${PROJECT_SOURCE_DIR}/include)

set(CMAKE_RUNTIME_OUTPUT_DIRECTORY ${PROJECT_SOURCE_DIR}/bin)

add_executable(${ProjectName}
    src/main.cpp
    ${PROJECT_SOURCE_DIR}/resources/icon.rc 
)