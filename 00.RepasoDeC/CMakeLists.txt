cmake_minimum_required(VERSION 3.22)

project(
    RepasoC
    VERSION 1.0.0
    DESCRIPTION "Repaso de lenguaje C para electrónica digital III"
    LANGUAGES C
)

set(CMAKE_C_STANDARD 11)

add_executable(helloWorld src/helloWorld.c)

add_executable(Main src/main.c src/dataType.c src/pointers.c src/struct.c)
target_include_directories(Main PRIVATE "inc/")

add_executable(LinkedList src/linkedList.c)