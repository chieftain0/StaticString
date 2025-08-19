cmake_minimum_required(VERSION 3.12)

set(ProjectName StaticString)

project(${ProjectName})

include_directories(${PROJECT_SOURCE_DIR}/include)

set(CMAKE_RUNTIME_OUTPUT_DIRECTORY ${PROJECT_SOURCE_DIR}/bin)

set(SOURCES
    src/main.cpp
)

# Add Windows-specific resources
if(WIN32)
    list(APPEND SOURCES ${PROJECT_SOURCE_DIR}/resources/icon.rc)
endif()

add_executable(${ProjectName} ${SOURCES})
