file(GLOB SOURCES 
	*.cpp
	sqlite/*.cpp
	pg/*.cpp
	../dbms/sqlite/*.c)

include_directories(.
	../dbms)

add_definitions(-D_USE_SQLITE)

add_library(db STATIC ${SOURCES})

