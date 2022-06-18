
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

#include "inputCommand.h"

int usartInit(struct inputCommand *usartDevice, char *ipAdress, char *port)
{
	if ((usartDevice->fd = serialOpen(usartDevice->deviceName, 9600)) == -1) {
		printf("usart module initialization failed - serial port opening failed!\r\n");
		return -1;
	}
	return 1;
}

int usartGetCommand(struct inputCommand *usartDevice)
{
	int nread = 0;
	memset(usartDevice->commandID, '\0',sizeof(usartDevice->commandID));
	nread = read(usartDevice->fd, usartDevice->commandID, sizeof(usartDevice->commandID));
	return nread;
}

struct inputCommand usartControl = {
	.commandName = "usart",
	.deviceName = "/dev/ttyAMA0",
	.commandID = {'\0'},
	.initCommand = usartInit,
	.getCommand = usartGetCommand,
	.log = {'\0'},
	.next = NULL,
};


/* 头插法 */
struct inputCommand *addusartControlToCommand(struct inputCommand *phead)
{
	if (phead == NULL) {
		return &usartControl;
	} else {
		usartControl.next = phead;
		phead = &usartControl;
	}
}



