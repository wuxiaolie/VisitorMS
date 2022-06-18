
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

#include "controlDevice.h"

int equipment2Open(struct controlDevice *equipmentNode) 
{
	digitalWrite(equipmentNode->pinNum, LOW);
	move(0, 0);
	printw("============ Welcome to Haoqing visitor management system ===========\n");
	printw("---------------------------------------------------------------------\n");
	printw("																	 \n");
	printw("																	 \n");
	printw("																	 \n");
	printw("---------------------------------------------------------------------\n");
	printw("-----------------------Equipment2 open seccess!----------------------\n");
	printw("-----------------------Enter any key to return-----------------------\n");
	printw("---------------------------------------------------------------------\n");
	printw("                                                                     \n");
	printw("																	 \n");
	printw("																	 \n");
	printw("                                                                     \n");
	printw("---------------------------------------------------------------------\n");
	refresh(); 
	getch();
}

int equipment2Close(struct controlDevice *equipmentNode)
{
	digitalWrite(equipmentNode->pinNum, HIGH);
	move(0, 0);
	printw("============ Welcome to Haoqing visitor management system ===========\n");
	printw("---------------------------------------------------------------------\n");
	printw("																	 \n");
	printw("                                                                     \n");
	printw("																	 \n");
	printw("---------------------------------------------------------------------\n");
	printw("-----------------------Equipment2 close seccess!---------------------\n");
	printw("-----------------------Enter any key to return-----------------------\n");
	printw("---------------------------------------------------------------------\n");
	printw("                                                                     \n");
	printw("																	 \n");
	printw("																	 \n");
	printw("																	 \n");
	printw("                                                                     \n");
	printw("---------------------------------------------------------------------\n");
	refresh(); 
	getch();
}

int equipment2Init(struct controlDevice *equipmentNode)
{
	pinMode(equipmentNode->pinNum, OUTPUT);
	digitalWrite(equipmentNode->pinNum, HIGH);
}

int equipment2Status(struct controlDevice *equipmentNode)
{
	move(0, 0);
	printw("============ Welcome to Haoqing visitor management system ===========\n");
	printw("---------------------------------------------------------------------\n");
	printw("																	 \n");
	printw("                                                                     \n");
	printw("																	 \n");
	printw("---------------------------------------------------------------------\n");

	if(digitalRead(equipmentNode->pinNum) == 0) {
		printw("-----------------------Equipment2 is open!---------------------------\n");
	} else {
		printw("-----------------------Equipment2 is close!--------------------------\n");
	}
	
	printw("-----------------------Enter any key to return-----------------------\n");
	printw("---------------------------------------------------------------------\n");
	printw("                                                                     \n");
	printw("																	 \n");
	printw("																	 \n");
	printw("                                                                     \n");
	printw("---------------------------------------------------------------------\n");
	refresh(); 
	getch();
}


struct controlDevice equipment2 = {
	.deviceName = "equipment2",
	.pinNum = 22,
	.open = equipment2Open,
	.close = equipment2Close,
	.deviceInit = equipment2Init,
	.readStatus = equipment2Status,
};

/* 头插法 */
struct controlDevice *addequipment2ToDevices(struct controlDevice *phead)
{
	if (phead == NULL) {
		return &equipment2;
	} else {
		equipment2.next = phead;
		phead = &equipment2;
	}
}





















