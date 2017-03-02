cmake_minimum_required(VERSION 3.6)
project(SET2)

set(CMAKE_CXX_STANDARD 11)

set(SOURCE_FILES main.cpp Game.cpp Game.h Card.cpp Card.h Tools.cpp Tools.h Deck.cpp Deck.h)
add_executable(SET2 ${SOURCE_FILES})