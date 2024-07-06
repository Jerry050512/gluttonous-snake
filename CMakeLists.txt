cmake_minimum_required(VERSION 3.17)
project(game)

set(SOURCE_FILES)
set(SOURCE_FILES ${SOURCE_FILES} game.c)
set(SOURCE_FILES ${SOURCE_FILES} snake.c)
set(SOURCE_FILES ${SOURCE_FILES} utils.c)

add_executable(game ${SOURCE_FILES})

install(TARGETS game DESTINATION bin)
