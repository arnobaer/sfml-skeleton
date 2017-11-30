cmake_minimum_required(VERSION 3.2)

project(
    sfml-skeleton
    VERSION 0.1
    LANGUAGES CXX
)

set(CMAKE_MODULE_PATH
    "${PROJECT_SOURCE_DIR}/cmake"
    "${PROJECT_SOURCE_DIR}/cmake/modules"
    ${CMAKE_MODULE_PATH}
)

set(INCLUDES
    ${SFML_INCLUDE_DIR}
    "include"
)

set(SOURCES
    "src/core/Application.cpp"
    "src/main.cpp"
)

# locate FSML
find_package(SFML 2 COMPONENTS system window graphics audio REQUIRED)

# locate PugiXML
find_package(PugiXML REQUIRED)
include_directories (BEFORE "${PUGIXML_INCLUDE_DIR}")

set(LIBRARIES
    ${PUGIXML_LIBRARIES}
    ${SFML_LIBRARIES}
)

include_directories(${INCLUDES})

add_definitions(-std=c++11 -Wall -g)

add_executable(${PROJECT_NAME} ${SOURCES})

target_link_libraries(${PROJECT_NAME} ${LIBRARIES})
