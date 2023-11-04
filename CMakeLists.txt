cmake_minimum_required(VERSION 3.25.0)
project(Cockoo)

option(BELL_TEST "Play Bell at start" OFF)

include(FetchContent)
FetchContent_Declare(SFML
	GIT_REPOSITORY https://github.com/SFML/SFML.git
	GIT_TAG 2.6.x)
FetchContent_MakeAvailable(SFML)

if (BELL_TEST)
	add_definitions(-DBELL_TEST)
endif()

add_executable(Cockoo Cuckoo.cpp)

target_link_libraries(Cockoo PRIVATE sfml-graphics sfml-window sfml-system sfml-audio)