#ifndef SNAKE_PROJEKT_POINT_HEADER_H
#define SNAKE_PROJEKT_POINT_HEADER_H

#include <stdbool.h>

/*! struktura punktu */
struct Point {
    /** Współrzędna X */
    int x;
    /** Współrzędna Y */
    int y;
};

bool points[40][40];

/**
 *funkcja tworząca punkt o losowych koordynatach
 * @return wskaźnik na wylosowany punkt
 */
struct Point *random_point();

/**
 *funkcja ustawiająca flagę zajętości na polu o zadanych koordynatach
 * @param x współrzędna X
 * @param y współrzędna Y
 */
void change_point_status(int x, int y);

#endif //SNAKE_PROJEKT_POINT_HEADER_H
