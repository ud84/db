file(GLOB SOURCES 
	*.cpp
	sqlite/*.cpp
	pg/*.cpp)

include_directories(.
	../dbms)

add_library(db STATIC ${SOURCES})

