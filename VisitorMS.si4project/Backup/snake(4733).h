

#include "menu.h"

#define UP 1
#define DOWN -1
#define LEFT 2
#define RIGHT -2

struct Snake // define the snake
{
    int hang;
    int lie;
    struct Snake *next;
};

struct Snake food; // define the food
struct Snake *head = NULL;
struct Snake *tail = NULL;
int key;
int dir;
int set = 49;
int nub = 4;

























