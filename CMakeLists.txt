cmake_minimum_required(VERSION 3.19)
project(webserv)

set(CMAKE_CXX_STANDARD 98)
set(CMAKE_CXX_FLAGS "-Wall -Wextra -Werror")

include_directories(includes)

file(GLOB_RECURSE SRCS "srcs/*.cpp")
file(GLOB_RECURSE REQ "srcs/config/*.cpp")
file(GLOB_RECURSE REQ_INC "srcs/config/*.hpp")

add_executable(webserv1 ${SRCS} ${REQ} ${REQ_INC})
