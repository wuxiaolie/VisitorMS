
/**********************************************************************************************
 *    :|x].              ?ObU:        +jfl           ?Zdr'                   '"I>>iI"'        
 *    n$$${             x@$$k;       n$$$Mi         [B$$$c               "-xZ*%$$$$$%*pX+     
 *    >8$$k`           j$$$C^       ]$$$$$Q.       `k$$$$8l            ~Y#$$%kQznnuY0qhk|     
 *     j$$$n          {@$$0'       .q$$$$$B<       ($$$$$$/          'uB$$p{:                 
 *     'm$$B+        +&$$b,        _@$$B$$$z      ;#$$8%$$Z.         +$$$M:                   
 *      !&$$b^      !*$$#!         C$$$\k$$M:    .Q$$@}X$$8!         ,w$$$bc|}-~<iI".         
 *       f$$$x     :k$$&+         _B$$p./$$$x    /$$$u +@$$x          '[YdW@$$$$$$$%oOr>      
 *       'w$$%~   ^w$$B}         `b$$@- "h$$Wl  _8$$O' 'p$$o"             ^:!><+](n0#$$@Z>    
 *        >8$$b^ 'L$$$\          x$$$C   )$$$C Io$$a;   ($$$t                       `[#$$*:   
 *         /$$$X.c$$$x          <8$$&l   .Z$$@\w$$%+    "a$$#;     ,]]"               p$$$>   
 *         .J$$@w$$$Y.         .O$$$n     >8$$$$$$t      \$$$J     0$$*\"         '!(p$$$u.   
 *          "d$$$$$Q'          >B$$%i      r$$$$$L.      ^a$$@{    _b$$$&qJvnnncCq#$$$&Q-     
 *           lh$$$Y'           [$$$U       `0$$@C^        {@$$a^    .+jQk&@$$$$$@&aOn[:       
 *            :\r]             '{x)^        .+}>           ?UJ).         ^:l>>>l:^.            
 *                                                                                           
 * Copyright (C) 2022 - 2023, HaoQing, <970407688@qq.com>.
 * <https://github.com/wuxiaolie/VisitorMS> & <https://gitee.com/yang-haoqing/visitor-ms.git>
 *
 * This software is licensed as described in the file COPYING, which you should have received 
 * as part of this distribution.
 *
 * You may opt to use, copy, modify, merge, publish, distribute and/or sell copies of 
 * the Software, and permit persons to whom the Software is furnished to do so, under 
 * the terms of the COPYING file.
 *
 *********************************************************************************************/

#include "camera.h"

/* 打开摄像头 */
void openCamera(void)
{
	/* 打印提示信息 */
	move(0, 0);
	printw("============ Welcome to Haoqing visitor management system ===========\n");
	printw("---------------------------------------------------------------------\n");
	printw("                                                                     \n");
	printw("                                                                     \n");
	printw("                                                                     \n");
	printw("                                                                     \n");
	printw("                                                                     \n");
	printw("                                                                     \n");
	printw("--------------------------Camera is starting!------------------------\n");
	printw("----------------------Open web page to view video--------------------\n");
	printw("----------------http://192.168.3.143:8080/index.html-----------------\n");
	printw("----------------Enter ctrl + c to turn off the camera----------------\n");
	printw("                                                                     \n");
	printw("                                                                     \n");
	printw("                                                                     \n");
	printw("                                                                     \n");
	printw("                                                                     \n");
	printw("                                                                     \n");
	printw("----------------------Enter any key to to continue-------------------\n");
	refresh(); 
	getch();

	/* 返回shell界面，正常打印摄像头启动信息 */
	endwin();

	/* 打开树莓派摄像头 */
	system("/home/pi/raspberry/mjpg-streamer/mjpg-streamer-experimental/start.sh");

	/* 摄像头使用结束后，重新打开ncurses界面 */
	initNcurse();

	/* 刷新界面 */
	//picRefresh();

	/* 打印退出信息 */
	move(0, 0);
	printw("============ Welcome to Haoqing visitor management system ===========\n");
	printw("---------------------------------------------------------------------\n");
	printw("                                                                     \n");
	printw("                                                                     \n");
	printw("                                                                     \n");
	printw("                                                                     \n");
	printw("                                                                     \n");
	printw("---------------------------------------------------------------------\n");
	printw("-----------------------Camera close seccess!-------------------------\n");
	printw("-----------------------Enter any key to return-----------------------\n");
	printw("---------------------------------------------------------------------\n");
	printw("                                                                     \n");
	printw("                                                                     \n");
	printw("                                                                     \n");
	printw("                                                                     \n");
	printw("                                                                     \n");
	printw("---------------------------------------------------------------------\n");
	refresh(); 
	getch();

	return;	
}

/* 关闭摄像头 */
void closeCamera(void)
{
	/* 打印退出信息 */
	move(0, 0);
	printw("============ Welcome to Haoqing visitor management system ===========\n");
	printw("---------------------------------------------------------------------\n");
	printw("                                                                     \n");
	printw("                                                                     \n");
	printw("                                                                     \n");
	printw("                                                                     \n");
	printw("                                                                     \n");
	printw("---------------------------------------------------------------------\n");
	printw("---------------------The camera is already off!----------------------\n");
	printw("-----------------------Enter any key to return-----------------------\n");
	printw("---------------------------------------------------------------------\n");
	printw("                                                                     \n");
	printw("                                                                     \n");
	printw("                                                                     \n");
	printw("                                                                     \n");
	printw("                                                                     \n");
	printw("---------------------------------------------------------------------\n");
	refresh(); 
	getch();

	return;	
}




