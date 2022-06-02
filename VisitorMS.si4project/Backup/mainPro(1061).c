
#include "mainPro.h"
#include "snake.h"

int main()
{	
	/*
	int snakeFlag = snakeGameStart();
	if (snakeFlag == -1) {
		printf("snake error\n");
		return -1;
	}
	*/

	/* 初始化wiringPi库 */
	if (wiringPiSetup() == -1) {
		printf("wiringPi setup error\n");
		return -1;
	}

	/* 显示起始界面 */
	int selectFunction = 0; //用于接受用户的选择

	while (true)
	{
		cout << "======================  欢迎来到传智播客机房预约系统  ====================="
			<< endl;
		cout << endl << "请输入您的身份" << endl;
		cout << "\t\t -------------------------------\n";
		cout << "\t\t|                               |\n";
		cout << "\t\t|          1.学生代表           |\n";
		cout << "\t\t|                               |\n";
		cout << "\t\t|          2.老    师           |\n";
		cout << "\t\t|                               |\n";
		cout << "\t\t|          3.管 理 员           |\n";
		cout << "\t\t|                               |\n";
		cout << "\t\t|          0.退    出           |\n";
		cout << "\t\t|                               |\n";
		cout << "\t\t -------------------------------\n";
		cout << "输入您的选择: ";

		printw("====================  欢迎来到皓清访客管理系统  =====================\n");
	    printw("---------------------------------------------------------------------\n");
	    printw("------------------  请输入数字选择验证登录的方式:  ------------------\n");
	    printw("\n");
	    printw("           \"1\"\n");
	    printw("  		   \"2\"\n");
	    printw(" 		   \"3\"\n");
	    printw("  		   \"4\"\n");
	    printw("       贪吃蛇游戏体验             \"5\"\n");
	    printw("---------------------------------------------------------------------\n");
	    printw("You want:");

		cin >> selectFunction; //接受用户选择

		switch (selectFunction) //根据用户选择 实现不同接口
		{
		case 1: //学生身份
			LoginIn(STUDENT_FILE, 1);
			break;
		case 2: //老师身份
			LoginIn(TEACHER_FILE, 2);
			break;
		case 3:  //管理员身份
			LoginIn(ADMIN_FILE, 3);
			break;
		case 0 :  //退出系统
			cout << "欢迎下一次使用" << endl;
			system("pause");
			return 0;
			break;
		default:
			cout << "输入有误，请重新选择！" << endl;
			system("pause");
			system("cls");
			break;
		}
	}







	return 0;	
}
