/*!
 * \authors Paweł Mróz
 * \date 06.05.2019
 * \bug Gdy uzytkownik zaraz po rozpoczeciu gry naciśnie strzałkę w górę, gra kończy się
 */


#include <GL/gl.h>
#include <GL/glut.h>
#include "../headers/main_header.h"
#include "../headers/snake_header.h"
#include "../headers/point_header.h"
#include "../headers/obstacle_list_header.h"

#define WIDTH  50
#define HEIGHT  50


int main(int argc, char **argv) {

    srand(time(NULL));
    snake = create_snake();
    foods = create_list();
    obstacles = create_obstacle_list();
    setup(&argc, argv);
    return 0;
}


void setup(int *argc, char **argv) {
    status = SUCCESS;

    glutInit(argc, argv);
    glutInitDisplayMode(GLUT_RGB | GLUT_DOUBLE);
    glutInitWindowSize(600,600);
    glutCreateWindow("SNAKE_GAME");
    glutDisplayFunc(show_window);
    glutReshapeFunc(reshape_window);
    glutTimerFunc(0, timer, 0);
    glutSpecialFunc(get_user_input);
    glutMainLoop();
}



void show_window() {
    if (status == FAIL || is_empty(snake.snakeQueue)) {
        glClear(GL_COLOR_BUFFER_BIT);
        end_game();
    } else {
        glClearColor(1, 0.8, 0.5, 1);
        glClear(GL_COLOR_BUFFER_BIT);
        status = move_snake(&snake);
        print_obstacle_list(*obstacles);
        print_list(*foods);
        display(snake);

    }
    glutSwapBuffers();
}

void reshape_window(int width, int height) {
    glViewport(0, 0, (GLsizei) width, (GLsizei) height);
    glMatrixMode(GL_PROJECTION);
    glLoadIdentity();
    glOrtho(0.0, WIDTH, 0.0, HEIGHT, -1.0, 1.0);
    glMatrixMode(GL_MODELVIEW);
}


void timer() {
    glutPostRedisplay();
    glutTimerFunc(80, timer, 0);
}

void get_user_input(int key) {
    switch (key) {
        case GLUT_KEY_LEFT:
            if (direction != RIGHT) {
                direction = LEFT;
            }
            break;
        case GLUT_KEY_RIGHT:
            if (direction != LEFT) {
                direction = RIGHT;
            }
            break;
        case GLUT_KEY_DOWN:
            if (direction != UP) {
                direction = DOWN;
            }
            break;
        case GLUT_KEY_UP:
            if (direction != DOWN) {
                direction = UP;
            }
            break;
        default:
            break;
    }
}

bool is_conflict(struct Snake *snake, int x, int y) {
    if (points[x][y]) {
        if (search_list(*foods, x, y)) {
            eat_food(snake, x, y);
            return true;
        }

        if (search_queue(snake->snakeQueue, x, y) || search_obstacle_list(*obstacles, x, y)) {
            return false;
        }
    }
    return true;
}


void end_game() {


    char end[64] = "Niestety, gra skonczona :/";
    char score[20];
    char message[64] = "Twoj wynik został zapisany.";



    sprintf(score, "Twoj wynik: %d", get_size(&snake.snakeQueue)-3);
    glColor3f(0, 0, 0);

    glPushMatrix();
    glTranslatef(10, 45, 0);
    glScalef(.02, .03, .03);
    for (int c = 0; end[c] != 0; ++c) {
        glutStrokeCharacter(GLUT_STROKE_ROMAN, end[c]);
    }
    glPopMatrix();

    glPushMatrix();
    glTranslatef(10, 20, 0);
    glScalef(.02, .02, .02);
    for (int j = 0; message[j] != 0; ++j) {
        glutStrokeCharacter(GLUT_STROKE_ROMAN, message[j]);
    }
    glPopMatrix();


    glPushMatrix();
    glTranslatef(15, 10, 0);
    glScalef(.02, .02, .02);
    for (int i = 0; score[i] != 0; ++i) {
        glutStrokeCharacter(GLUT_STROKE_ROMAN, score[i]);
    }
    glPopMatrix();


}


