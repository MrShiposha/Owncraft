IF(${CMAKE_SYSTEM_NAME} STREQUAL "Windows")
	ADD_DEFINITIONS(-D_CRT_SECURE_NO_WARNINGS)
ENDIF()