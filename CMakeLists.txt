cmake_minimum_required(VERSION 3.14)
project(Snake_Projekt C)

set(CMAKE_C_STANDARD 99)

add_executable(Snake_Projekt source/main.c headers/food_list_header.h headers/main_header.h headers/point_header.h headers/snake_header.h source/food_list.c source/point.c source/snake.c headers/obstacle_list_header.h source/obstacle_list.c)

target_link_libraries(Snake_Projekt GL)
target_link_libraries(Snake_Projekt glut)
