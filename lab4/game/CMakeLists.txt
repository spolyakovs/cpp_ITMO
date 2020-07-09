project(game)

set(SOURCES
		game.cpp structures.cpp)
set(HEADERS
		game.h
		structures.h)

include_directories(../)

add_library(game ${SOURCES} ${HEADERS})
