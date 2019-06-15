#include <GL/gl.h>
#include <GL/glut.h>
#include "../headers/snake_header.h"
#include "../headers/point_header.h"
#include "../headers/main_header.h"
#include "../headers/obstacle_list_header.h"
#include <time.h>


bool push_front(struct snake_queue *queue, int x, int y) {
    struct snake_queue_node *new_node = (struct snake_queue_node *) malloc(sizeof(struct snake_queue_node));

    if (new_node == NULL) {
        return false;
    }

    new_node->x = x;
    new_node->y = y;
    new_node->next = NULL;
    new_node->prev = NULL;
    if (queue->head == NULL) {
        queue->head = queue->tail = new_node;
    } else {
        queue->tail->next = new_node;
        new_node->prev = queue->tail;
        queue->tail = new_node;
    }

    change_point_status(new_node->x, new_node->y);
    queue->size++;
    return true;
}

bool push_back(struct snake_queue *queue, int x, int y) {
    struct snake_queue_node *new_node = (struct snake_queue_node *) malloc(sizeof(struct snake_queue_node));

    if (new_node == NULL) {
        return false;
    }

    new_node->x = x;
    new_node->y = y;
    new_node->next = NULL;
    new_node->prev = NULL;

    if (queue->head == NULL) {
        queue->head = queue->tail = new_node;
    } else {
        queue->head->prev = new_node;
        new_node->next = queue->head;
        queue->head = new_node;
    }

    change_point_status(new_node->x, new_node->y);
    queue->size++;
    return true;
}

bool pop_back(struct snake_queue *queue) {
    if (queue->tail == NULL) {
        return false;
    }

    change_point_status(queue->tail->x, queue->tail->y);
    struct snake_queue_node *tmp = queue->tail->prev;
    free(queue->tail);
    queue->tail = tmp;
    if (tmp == NULL) {
        queue->head = NULL;
    } else {
        queue->tail->next = NULL;
    }

    queue->size--;
    return true;
}

struct Snake create_snake() {
    struct snake_queue *snakeQueue = (struct snake_queue *) malloc(sizeof(struct snake_queue));


    for (int i = 22; i < 25; i++) {
        push_front(snakeQueue, 25, i);
    }


    struct Snake snake = {*snakeQueue};

    return snake;
}

void save_to_file() {
    time_t t = time(NULL);
    struct tm tm = *localtime(&t);

    FILE *f = fopen("../results.txt", "a");

    int i;
    i = get_size(&snake.snakeQueue) - 3;
    fprintf(f, "%d-%d-%d %d:%d:%d ", tm.tm_year + 1900, tm.tm_mon + 1, tm.tm_mday, tm.tm_hour, tm.tm_min, tm.tm_sec);
    fprintf(f, "Wynik: %d\n", i);
    fclose(f);
}


bool go_up(struct Snake *snake) {
    int new_x = snake->snakeQueue.head->x, new_y = snake->snakeQueue.head->y + 1;

    if (!is_conflict(snake, new_x, new_y) || new_y >= 50) {
        save_to_file();
        return false;
    }

    pop_back(&snake->snakeQueue);
    push_back(&snake->snakeQueue, new_x, new_y);

    return true;
}

bool go_down(struct Snake *snake) {
    int new_x = snake->snakeQueue.head->x, new_y = snake->snakeQueue.head->y - 1;

    if (!is_conflict(snake, new_x, new_y) || new_y < 0) {
        save_to_file();
        return false;
    }

    pop_back(&snake->snakeQueue);
    push_back(&snake->snakeQueue, new_x, new_y);

    return true;
}

bool go_left(struct Snake *snake) {
    int new_x = snake->snakeQueue.head->x - 1, new_y = snake->snakeQueue.head->y;

    if (!is_conflict(snake, new_x, new_y) || new_x < 0) {
        save_to_file();
        return false;
    }

    pop_back(&snake->snakeQueue);
    push_back(&snake->snakeQueue, new_x, new_y);

    return true;
}

bool go_right(struct Snake *snake) {
    int new_x = snake->snakeQueue.head->x + 1, new_y = snake->snakeQueue.head->y;

    if (!is_conflict(snake, new_x, new_y) || new_x >= 50) {
        save_to_file();
        return false;
    }

    pop_back(&snake->snakeQueue);
    push_back(&snake->snakeQueue, new_x, new_y);

    return true;
}

enum status move_snake(struct Snake *snake) {
    switch (direction) {
        case UP:
            if (!go_up(snake)) return FAIL;
            break;
        case DOWN:
            if (!go_down(snake)) return FAIL;
            break;
        case RIGHT:
            if (!go_right(snake)) return FAIL;
            break;
        case LEFT:
            if (!go_left(snake)) return FAIL;
            break;
        default:
            break;
    }

    return SUCCESS;
}

void eat_food(struct Snake *snake, int x, int y) {

    bool isToxic;
    delete_node(&foods, x, y, &isToxic);

    if (isToxic) {
        pop_back(&snake->snakeQueue);
    } else {
        push_front(&snake->snakeQueue, x + 1, y + 1);
    }

    insert_node(&foods);

    if ((snake->snakeQueue.size) % 5 == 0) {
        int i;
        for (int i = 0; i < 20; i++) {
            remove_list_obstacle(&obstacles);
        }

    }

    if ((snake->snakeQueue.size) % 6 == 0) {
        int i;
        for (int i = 0; i < 30; i++) {
            insert_obstacle(&obstacles);
        }

    }
}


void display(struct Snake snake) {
    glColor3d(0, 1, 1);
    struct snake_queue_node *head = snake.snakeQueue.head;
    glRectd(head->x, head->y, head->x + 1, head->y + 1);

    head = head->next;
    glColor3d(0, 0, 0);

    while (head != NULL) {
        glRectd(head->x, head->y, head->x + 1, head->y + 1);
        head = head->next;
    }
}


bool search_queue(struct snake_queue queue, int x, int y) {
    while (NULL != queue.head) {
        if (queue.head->x == x && queue.head->y == y) {
            return true;
        }

        queue.head = queue.head->next;
    }

    return false;
}


int get_size(struct snake_queue *queue) {
    return queue->size;
}

bool is_empty(struct snake_queue queue) {
    return queue.size == 0;
}