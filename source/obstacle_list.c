#include <GL/gl.h>
#include <GL/glut.h>
#include "../headers/obstacle_list_header.h"
#include "../headers/point_header.h"
#include "../headers/main_header.h"

struct obstacle_list *create_obstacle_list() {
    struct obstacle_list_node *new_noe = (struct obstacle_list_node *) malloc(sizeof(struct obstacle_list_node));
    struct obstacle_list *list = (struct obstacle_list *) malloc(sizeof(struct obstacle_list));
    struct Point *point;

    if (NULL != new_noe) {
        point = random_point();
        new_noe->x = point->x;
        new_noe->y = point->y;
        new_noe->next = NULL;

        list->front = new_noe;
    }

    for (int i = 0; i < 40; i++) {
        insert_obstacle(&list);
    }

    return list;
}

struct obstacle_list *insert_to_obstacles_front(struct obstacle_list *list, struct obstacle_list_node *new_node) {
    new_node->next = list->front;
    list->front = new_node;
    return list;
}

bool insert_obstacle(struct obstacle_list **list) {
    if (NULL == list) {
        return false;
    }

    struct obstacle_list_node *new_node = (struct obstacle_list_node *) malloc(sizeof(struct obstacle_list_node));
    struct Point *point;

    if (NULL != new_node) {
        point = random_point();
        new_node->x = point->x;
        new_node->y = point->y;
        new_node->next = NULL;

        *list = insert_to_obstacles_front(*list, new_node);
    }

    return true;
}

void print_obstacle_list(struct obstacle_list list) {
    for (; NULL != list.front; list.front = list.front->next) {
        glColor3f(0.4, 0.4, 0.4);
        glRectd(list.front->x, list.front->y, list.front->x + 1, list.front->y + 1);
    }
}

bool search_obstacle_list(struct obstacle_list list, int x, int y) {
    for (; NULL != list.front; list.front = list.front->next) {
        if (list.front->x == x && list.front->y == y) {
            return true;
        }
    }

    return false;
}


void remove_list_obstacle(struct obstacle_list **list) {

    struct obstacle_list_node *next = (*list)->front->next;
    free((*list)->front);
    (*list)->front = next;

}

