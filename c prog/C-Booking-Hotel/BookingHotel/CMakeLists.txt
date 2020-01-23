cmake_minimum_required(VERSION 3.10)
project(BookingHotel C)

set(CMAKE_C_STANDARD 99)
set(CMAKE_MODULE_PATH ${CMAKE_MODULE_PATH} "${CMAKE_CURRENT_SOURCE_DIR}/cmake")

add_compile_options(-l sqlite3)
add_executable(BookingHotel main.c Hotel.h Admin.h User.h)

find_package (sqlite3)
if (SQLITE3_FOUND)
    include_directories(${SQLITE3_INCLUDE_DIRS})
    target_link_libraries (BookingHotel ${SQLITE3_LIBRARIES})
endif (SQLITE3_FOUND)


