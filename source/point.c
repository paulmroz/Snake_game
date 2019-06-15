#include <stdlib.h>
#include "../headers/point_header.h"
#include "../headers/main_header.h"

struct Point *random_point() {
    struct Point *new_point = (struct Point *) malloc(sizeof(struct Point));

    if (new_point != NULL) {
        do {
            new_point->x = rand() % 49 + 1;
            new_point->y = rand() % 49 + 1;
        } while (points[new_point->x][new_point->y]);
    }

    change_point_status(new_point->x, new_point->y);

    return new_point;
}

void change_point_status(int x, int y) {
    points[x][y] = points[x][y] ? false : true;
}
