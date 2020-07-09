project(strategies)
set(SOURCES
		human.cpp
        computer_random.cpp
		computer_min_y.cpp
		computer_interface.cpp)
set(HEADERS
		human.h
        computer_random.h
		computer_min_y.h
		interface.h
		computer_interface.h)

include_directories(../)

add_library(strategies ${SOURCES} ${HEADERS})
