#ifndef SNAKE_PROJEKT_FOOD_LIST_HEADER_H
#define SNAKE_PROJEKT_FOOD_LIST_HEADER_H

#include <stdbool.h>
#include <stdlib.h>
#include <stdio.h>
#include "../headers/main_header.h"

/*! struktura listy owoców, lista jednokierunkowa */
struct food_list_node {
    /** Współrzędna X */
    int x;
    /** Współrzędna Y */
    int y;
    /** Flaga określająca czy owoc był toksyczny */
    bool is_toxic;
    /** Wskaźnik na kolejny element w liście */
    struct food_list_node *next;
};

/*! typ bazowy listy owoców */
struct food_list {
    /** Wskaźnik na początek listy*/
    struct food_list_node *front;
};

/*! funkcja tworząca listę owoców
 * @return lista stworzona przez funkcje
 */
struct food_list *create_list();

/*! funkcja dodająca element na początek listy
 * @return lista po dodaniu element
 */
struct food_list *insert_front(struct food_list *, struct food_list_node *);

/*! funkcja dodająca do listy owoc o losowym położeniu i prawdopodobieństwie 0.1 na bycie toksycznym
 * @return flaga określająca czy dodawanie się powiodło
 */
bool insert_node(struct food_list **);

/*!funkcja znajdująca owoc, który znajduje sie w liście przed owocem o podanych współrzędnych
 * @return szukany owoc
 */
struct food_list_node *find_prev_node(struct food_list_node *, int, int);

/*!
 *funkcja usuwająca element w liście owoców za podanym elementem
 */
void delete_after(struct food_list_node *);

/*!
 *funkcja usuwająca element o podanych współrzędnych
 * @param y współrzędna Y
 * @param x współrzędna X
 * @return flaga określająca czy owoc został odlaneziony
 */
bool delete_node(struct food_list **, int y, int x,  bool *isToxic);

/*!
 *funkcja drukująca daną listę owoców na ekran
 */
void print_list(struct food_list);

/*!
 *funkcja określająca czy w liście owoców znajduje się owoc o zadanych współrzędnych
 * @param y współrzędna Y
 * @param x współrzędna X
 * @return flaga określająca czy owoc został odlaneziony
 */
bool search_list(struct food_list, int, int);

#endif //SNAKE_PROJEKT_FOOD_LIST_HEADER_H
