#ifndef SNAKE_PROJEKT_OBSTACLE_LIST_HEADER_H
#define SNAKE_PROJEKT_OBSTACLE_LIST_HEADER_H
#include <stdbool.h>

/*! struktura listy przeszkód (lista jednokierunkowa) */
struct obstacle_list_node {
    /** Współrzędna X */
    int x;
    /** Współrzędna Y */
    int y;
    /** Wskaźnik na kolejny element listy przeszkód */
    struct obstacle_list_node *next;
};

/** typ bazowy listy przeszkód */
struct obstacle_list {
    /** Wskaźnik na początek listy */
    struct obstacle_list_node *front;
};

/**
 *funkcja tworząca listę przeszkód
 * @return wskaźnik na strukturę listy przeszkód po zmianach
 */
struct obstacle_list *create_obstacle_list();

/**
 *funkcja wstawiająca element na początek listy przeszkód
 * @return wskaźnik na strukturę listy przeszkód po zmianach
 */
struct obstacle_list *insert_to_obstacles_front(struct obstacle_list *, struct obstacle_list_node *);

/**
 * funkcja dodająca przeszkodę do listy
 * @return flaga określająca czy dodawanie się powiodło
 */
bool insert_obstacle(struct obstacle_list **);

/**
 * funkcja drukująca listę przeszkód
 */
void print_obstacle_list(struct obstacle_list);

/**
 *funkcja wyszukująca przeszkodę w liście o zadanych koordynatach
 *@return
 */
bool search_obstacle_list(struct obstacle_list, int x, int y);


/**
 *funkcja usuwająca przeszkodę z listy
 *@return
 */
void remove_list_obstacle(struct obstacle_list **list);



#endif //SNAKE_PROJEKT_OBSTACLE_LIST_HEADER_H
