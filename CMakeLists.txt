cmake_minimum_required(VERSION 3.25.0)
project(Cockoo)

option(BELL_TEST "Play Bell at start" OFF)
option(BUILD_SHARED_LIBS "Build shared libraries" OFF)

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

if(WIN32)
    add_custom_command(
        TARGET Cockoo
        COMMENT "Copy OpenAL DLL"
        PRE_BUILD COMMAND ${CMAKE_COMMAND} -E copy ${SFML_SOURCE_DIR}/extlibs/bin/$<IF:$<EQUAL:${CMAKE_SIZEOF_VOID_P},8>,x64,x86>/openal32.dll $<TARGET_FILE_DIR:Cockoo>
        VERBATIM)
endif()

add_custom_command(
    TARGET Cockoo
    COMMENT "COPY INSTALLER BAT"
    PRE_BUILD COMMAND ${CMAKE_COMMAND} -E copy "${CMAKE_SOURCE_DIR}/INSTALL.bat" $<TARGET_FILE_DIR:Cockoo>
    VERBATIM)

add_custom_command(
    TARGET Cockoo
    COMMENT "COPY UNINSTALLER BAT"
    PRE_BUILD COMMAND ${CMAKE_COMMAND} -E copy "${CMAKE_SOURCE_DIR}/UNINSTALL.bat" $<TARGET_FILE_DIR:Cockoo>
    VERBATIM)