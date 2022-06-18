
#include "snake.h"

/* 初始化食物随机出现位置 */
static void initFood() 
{
    int x = rand() % 20;
    int y = (rand() % 19) + 1;
    food.hang = x;
    food.lie = y;
}

/* 判断是否吃到食物 */
static int hasFood(int i, int j) 
{
    if (food.hang == i && food.lie == j)
    {
        return 1;
    }
    return 0;
}

/* 判断是否触碰到自己的身体 */
static int hasSnakeNode(int i, int j) 
{
    struct Snake *p;
    p = head;
    while (p != NULL)
    {
        if (p->hang == i && p->lie == j)
        {
            return 1;
        }
        p = p->next;
    }
    return 0;
}

/* 删除蛇的节点 */
static void deleNode() 
{
    struct Snake *p;
    p = head;
    head = head->next;
    free(p);
}

/* 增加蛇的结点 */
static void addNode() 
{
    struct Snake *new = (struct Snake *)malloc(sizeof(struct Snake));

    new->next = NULL;

    switch (dir)
    {
    case UP:
        new->hang = tail->hang - 1;
        new->lie = tail->lie;
        break;
    case DOWN:
        new->hang = tail->hang + 1;
        new->lie = tail->lie;
        break;
    case LEFT:
        new->hang = tail->hang;
        new->lie = tail->lie - 1;
        break;
    case RIGHT:
        new->hang = tail->hang;
        new->lie = tail->lie + 1;
        break;
    }
    tail->next = new;
    tail = new;
}

/* 初始化蛇 */
static void initSnake() 
{
    struct Snake *p;

    dir = RIGHT;

    while (head != NULL)
    {
        p = head;
        head = head->next;
        free(p);
    }
    initFood();
    head = (struct Snake *)malloc(sizeof(struct Snake));
    head->hang = 1;
    head->lie = 1;
    head->next = NULL;

    tail = head;
    addNode();
    addNode();
    addNode();
}

/* 判断是否吃到自己或者边界 */
static int ifSnakeDie() 
{
    struct Snake *p;
    p = head;
    if (tail->hang < 0 || tail->lie == 0 || tail->hang == 20 || tail->lie == 20)
    {
        return 1;
    }
    while (p->next != NULL)
    {
        if (p->hang == tail->hang && p->lie == tail->lie)
            return 1;
        p = p->next;
    }
    return 0;
}

/* 转向 */
static void turn(int direction)
{
    if (set != 49 && set != 50 && set != 53)
    {
        if (abs(dir) != abs(direction))
        {
            dir = direction;
        }
    }
    else
        dir = direction;
}

/* 转向 */
static void changeDir() 
{
    while (1)
    {
        if (set != 53)
        {
            key = getch();
            switch (key)
            {
            case KEY_DOWN:
                turn(DOWN); //-1
                break;
            case KEY_UP:
                turn(UP); // 1
                break;
            case KEY_LEFT:
                turn(LEFT); // 2
                break;
            case KEY_RIGHT:
                turn(RIGHT); //-2
                break;
            }
        }
        else   //自动模式
        {
            if (tail->hang > food.hang)
                turn(UP);
            else if (tail->hang < food.hang)
                turn(DOWN);
            if (tail->lie > food.lie)
                turn(LEFT);
            else if (tail->lie < food.lie)
                turn(RIGHT);
        }
    }
}

/* 移动蛇 */
static void moveSnake() 
{
    addNode();
    if (hasFood(tail->hang, tail->lie))
    {
        initFood();
        nub++; // judge whether win
    }
    else
        deleNode();
    if (set != 49 && set != 50 && set != 53)
    {
        if (ifSnakeDie())
            initSnake();
    }
}

/* 绘制整个图形界面 */
static void gamePic() 
{
    int hang;
    int lie;
    move(0, 0);
    for (hang = 0; hang < 20; hang++) // 20*20 size map
    {
        if (hang == 0)
        {
            for (lie = 0; lie < 20; lie++)
            {
                printw("--");
            }
            printw("\n");
        }
        if (hang >= 0 && hang <= 19)
        {
            for (lie = 0; lie <= 20; lie++)
            {
                if (lie == 0 || lie == 20)
                    printw("|");
                else if (hasSnakeNode(hang, lie))
                {
                    printw("[]");
                }
                else if (hasFood(hang, lie))
                {
                    printw("##");
                }
                else
                    printw("  ");
            }
            printw("\n");
        }
        if (hang == 19)
        {
            for (lie = 0; lie < 20; lie++)
            {
                printw("--");
            }
            printw("\n");
        }
    }
    printw("by HaoQing, Happy Game!\n");
    switch (dir)
    {
    case UP:
        printw("Snake UP!   \n");
        break;
    case DOWN:
        printw("Snake DOWN! \n");
        break;
    case LEFT:
        printw("Snake LEFT! \n");
        break;
    case RIGHT:
        printw("Snake RIGHT!\n");
        break;
    }
    if (nub >= 300)
    {
        printw("------------------------------------\n");
        printw("==============YOU WIN!==============\n");
        printw("------------------------------------\n");
	}
}

/* 刷新界面 */
static void refreshJieMian() 
{
    while (1)
    {
        moveSnake();
        gamePic();
        refresh();
        switch (set)
        {
        case 49:
            usleep(200000);
            break;
        case 50:
            usleep(100000);
            break;
        case 51:
            usleep(100000);
            break;
        case 52:
            usleep(80000);
            break;
        case 53:
            usleep(70000);
            break;
        default:
            usleep(150000);
        }
    }
}

/* 贪吃蛇游戏总入口 */
int snakeGameStart(void)
{
	/* 清屏 */
	picRefresh();

	/* 打印模式选择界面 */
	picOfSnakeGame();

	//fflush(stdin);
	//fflush(stdout);

	key == RIGHT;               // 重新初始化
	set == 49;
    set = getch();              // 如果输入的不是规定数字，则按默认模式启动
    if (set == 113) {           // 如果输入的是q，则直接返回上一级
		return 0;
	}

	pthread_t t1;
    pthread_t t2;

	//endwin();
	//initNcurse();
		
    initSnake();
    gamePic();

	/* 创建两个线程，一个线程用于不断刷新界面，一个线程用于不断接收用户输入的上下左右方向信息 */
	int ret;
	ret = pthread_create(&t1, NULL, (void *)refreshJieMian, NULL);
	if (ret) {
		fprintf(stderr, "Error: %s\n", strerror(ret));
	 	exit(-1);
	}
   	ret = pthread_create(&t2, NULL, (void *)changeDir, NULL);
	if (ret) {
		fprintf(stderr, "Error: %s\n", strerror(ret));
	 	exit(-1);
	}
	
    while (1) {
		if (key == 113) {      //q的ASCII码为113
			
			/* 取消线程 */
			pthread_cancel(t1);
			pthread_cancel(t2);

			/* 回收线程 */
			pthread_join(t1, NULL);
			pthread_join(t2, NULL);
			
			picRefresh();
			break;
		}
	}
	
    //endwin();
    return 0;
}

















