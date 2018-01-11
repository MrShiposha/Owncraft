CMAKE_MINIMUM_REQUIRED(VERSION 3.8)
PROJECT(Owncraft)

INCLUDE(cmakemodules/includes.cmake)
INCLUDE(cmakemodules/libraries.cmake)
INCLUDE(cmakemodules/sources.cmake)
INCLUDE(cmakemodules/definitions.cmake)


ADD_EXECUTABLE(${CMAKE_PROJECT_NAME} ${SOURCES})
TARGET_LINK_LIBRARIES(${CMAKE_PROJECT_NAME} ${LIBRARIES})

INCLUDE(cmakemodules/postbuild.cmake)