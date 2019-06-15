#ifndef SNAKE_PROJEKT_SNAKE_HEADER_H
#define SNAKE_PROJEKT_SNAKE_HEADER_H

#include <stdbool.h>
#include <stdlib.h>
#include "main_header.h"
#include "food_list_header.h"

/** struktura kolejki węża oparta o wiązaną listę dwukierunkową */
struct snake_queue_node {
    /** Współrzędna X */
    int x;
    /** Współrzędna Y */
    int y;
    /** Wskaźnik na następny element węża */
    struct snake_queue_node *next;
    /** Wskaźnik na poprzedni element węża */
    struct snake_queue_node *prev;

};

/** typ bazowy kolejki węża */
struct snake_queue {
    struct snake_queue_node *head, *tail;
    unsigned int size;
};

/** typ bazowy przechowujący informacje o wężu */
struct Snake {
    /** Pole przechowujące kolejkę elementów węża */
    struct snake_queue snakeQueue;
};

/**
 *funkcja tworząca wężą
 * @return struktura przechowująca typ bazowy węża
 */
struct Snake create_snake();

/**
 *funkcja przemieszczająca węża w górę
 * @return flaga informująca o tym czy nastąpiła kolizja
 */
bool go_up(struct Snake *);

/**
 * funkcja przemieszczająca węża w dół
 * @return flaga informująca o tym czy nastąpiła kolizja
 */
bool go_down(struct Snake *);

/**
 * funkcja przemieszczająca węża w prawo
 * @return flaga informująca o tym czy nastąpiła kolizja
 */
bool go_right(struct Snake *);

/**
 * funkcja przemieszczająca węża w lewo
 * @return flaga informująca o tym czy nastąpiła kolizja
 */
bool go_left(struct Snake *);

/**
 * funkcja określająca czy dany ruch się powiódł
 * @return wartość wyliczenia informująca czy dany ruch zakończył się sukcesem
 */
enum status move_snake(struct Snake *);

/**
 * funkcja usuwająca owoc o podanych koordynatach wykonując efekt "zjadania" czyli dodaje lub odejmuje długość węża
 * @param x współrzędna X
 * @param y współrzędna Y
 */
void eat_food(struct Snake *, int x, int y);

/**
 * funkcja wyświetlająca węża
 */
void display(struct Snake);

/**
 *funkcja dodająca element o podanych współrzędnych na początek kolejki
 * @return flaga określająca czy dodawanie się powiodło
 */

bool push_front(struct snake_queue *, int x, int y);

/**
 * funkcja dodająca element o podanych koordynatach na koniec kolejki
 * @return flaga określająca czy dodawanie się powiodło
 */
bool push_back(struct snake_queue *, int x, int y);

/**
 * funkcja zdejmująca element z końca kolejki
 * @return flaga określająca czy zdejmowanie się powiodło
 */
bool pop_back(struct snake_queue *);

/**
 * funkcja określająca czy w kolejce występuje element o podanych koordynatach
 * @return flaga określająca czy podany element wystąpił
 */
bool search_queue(struct snake_queue, int x, int y);

/**
 * funkcja pobierająca ilość elementów w kolejce węża
 * @return ilość elementów w kolejce węża
 */
int get_size(struct snake_queue *);

/**
 * funkcja określająca czy kolejka węża jest pusta
 * @return flaga określająca czy kolejka jest pusta
 */
bool is_empty(struct snake_queue queue);

#endif //SNAKE_PROJEKT_SNAKE_HEADER_H
