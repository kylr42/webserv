cmake_minimum_required(VERSION 3.20)
project(webserv)

set(CMAKE_CXX_STANDARD 98)
set(CMAKE_CXX_FLAGS "-Wall -Wextra -Werror -Wshadow -Wno-shadow ")

include_directories(includes)

file(GLOB_RECURSE SRCS "srcs/*.cpp")

add_executable(webserv ${SRCS})
