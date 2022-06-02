
#include "menu.h"

#define UP 1
#define DOWN -1
#define LEFT 2
#define RIGHT -2

/* 定义蛇结点结构体 */
struct Snake 
{
    int hang;
    int lie;
    struct Snake *next;
};

/* 贪吃蛇游戏用的的静态全局变量 */
static struct Snake food; // define the food
static struct Snake *head = NULL;
static struct Snake *tail = NULL;
static int key = RIGHT;
static int dir = 0;
static int set = 49;
static int nub = 4;

/* 贪吃蛇游戏总入口 */
int snakeGameStart(void);
























