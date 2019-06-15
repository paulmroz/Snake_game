#include <GL/gl.h>
#include <GL/glut.h>
#include "../headers/food_list_header.h"
#include "../headers/point_header.h"

struct food_list *create_list() {
    struct food_list_node *new_node = (struct food_list_node *) malloc(sizeof(struct food_list_node));
    struct food_list *list = (struct food_list *) malloc(sizeof(struct food_list));
    struct Point *point;

    if (new_node != NULL) {
        point = random_point();
        new_node->x = point->x;
        new_node->y = point->y;
        new_node->is_toxic = (rand() % 101) > 90 ? true : false;
        new_node->next = NULL;

        list->front = new_node;
    }

    for (int i = 0; i < 4; i++) {
        insert_node(&list);
    }

    return list;
}

struct food_list *insert_front(struct food_list *list, struct food_list_node *new_node) {
    new_node->next = list->front;
    list->front = new_node;
    return list;
}

bool insert_node(struct food_list **list) {
    if (list == NULL) {
        return false;
    }

    struct food_list_node *new_node = (struct food_list_node *) malloc(sizeof(struct food_list_node));
    struct Point *point;

    if (new_node != NULL) {
        point = random_point();
        new_node->x = point->x;
        new_node->y = point->y;
        new_node->is_toxic = (rand() % 101) > 90 ? true : false;
        new_node->next = NULL;

        *list = insert_front(*list, new_node);
    }

    return true;
}

struct food_list_node *find_prev_node(struct food_list_node *front, int x, int y) {
    struct food_list_node *prev = front;
    while (((front->x != x) && (front->y != y)) && front) {
        prev = front;
        front = front->next;
    }
    return prev;
}

void delete_after(struct food_list_node *node) {
    struct food_list_node *next = NULL != node ? node->next : NULL;
    if (next != NULL) {
        node->next = next->next;
        free(next);
    }
}

bool delete_node(struct food_list **list, int x, int y, bool *is_toxic) {
    if (list == NULL) {
        return false;
    }

    if (((*list)->front->x == x) && ((*list)->front->y == y)) {
        *is_toxic = (*list)->front->is_toxic;
        struct food_list_node *next = (*list)->front->next;
        free((*list)->front);
        (*list)->front = next;
    } else {
        struct food_list_node *prev = find_prev_node((*list)->front, x, y);
        *is_toxic = NULL == prev->next ? prev->is_toxic : prev->next->is_toxic;
        delete_after(prev);
    }

    return true;
}

void print_list(struct food_list list) {
    for (; list.front != NULL; list.front = list.front->next) {
        if (true == list.front->is_toxic) {
            glColor3d(1.0, 0.0, 0.0);
        } else {
            glColor3d(0.0, 1.0, 0.0);
        }
        glRectd(list.front->x, list.front->y, list.front->x + 1, list.front->y + 1);
    }
}

bool search_list(struct food_list list, int x, int y) {
    for (; list.front != NULL; list.front = list.front->next) {
        if (list.front->x == x && list.front->y == y) {
            return true;
        }
    }
    return false;
}
