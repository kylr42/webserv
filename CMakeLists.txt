cmake_minimum_required(VERSION 3.19)
project(webserv)

set(CMAKE_CXX_STANDARD 98)
set(CMAKE_CXX_FLAGS "-Wall -Wextra -Werror")

include_directories(includes)
include_directories(includes/utils)
include_directories(includes/config)
include_directories(includes/exceptions)

file(GLOB_RECURSE SRCS "srcs/*.cpp")
file(GLOB_RECURSE REQ "srcs/config/*.cpp")

add_executable(webserv ${SRCS} ${REQ} ${REQ_INC})
