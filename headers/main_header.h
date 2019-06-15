#ifndef SNAKE_PROJEKT_MAIN_HEADER_H
#define SNAKE_PROJEKT_MAIN_HEADER_H

#include <time.h>
#include <stdlib.h>
#include "food_list_header.h"
#include "./snake_header.h"

/** typ wyliczeniowy reprezentujący kierunek węża */
enum way {
    UP = 1,
    DOWN,
    RIGHT,
    LEFT
} direction;

enum status {
    FAIL = 0,
    SUCCESS
} status;
/**zmienna globalna reprezentująca listę owoców na planszy */
struct food_list *foods;

/**zmienna globalna reprezentująca obecny stan węża */
struct Snake snake;

/**zmienna globalna reprezentująca listę przeszkód na planszy */
struct obstacle_list *obstacles;

/**
 *funkcja inicjująca bibliotekę GLUT
 * @param argc
 * @param argv
 */
void setup(int *argc, char **argv);

/** funkcja inicjująca okno gry */
void show_window();

/**
 * funkcja ustawiająca okno gry
 * @param width
 * @param height
 */
void reshape_window(int width, int height);

/**
 *funkcja pomocnicza do obliczania szybkosci weża
 */
void timer();

/**
 *funkcja pobierająca klawisz naciśnięty przez gracza, oraz ustawiająca kierunek w którym porusza się wąż
 */
void get_user_input(int key);

/**
 *funkcja sprawdzajace czy waż koliduje z pokarmem
 * @param snake struktura węża
 * @param x współrzędna X
 * @param y współrzędna Y
 * @return flaga określająca czy wystąpiła kolizja
 */
bool is_conflict(struct Snake *snake, int x, int y);

/**
 *funkcja kończąca grę, wyświetla napisy końcowe
 */
void end_game();

#endif //SNAKE_PROJEKT_MAIN_HEADER_H
