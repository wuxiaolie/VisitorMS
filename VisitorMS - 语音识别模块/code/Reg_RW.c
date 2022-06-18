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
 *  工程名称：YS-V0.7语音识别模块驱动程序
 *	CPU: STC11L08XE
 *	晶振：22.1184MHZ
 *	波特率：9600 bit/S
 *	配套产品信息：YS-V0.7语音识别开发板
 *  说明：口令模式： 即每次识别时都需要说“小杰”这个口令 ，才能够进行下一级的识别
 *
 *********************************************************************************************/

#include "config.h"

		#define LD_INDEX_PORT		(*((volatile unsigned char xdata*)(0x8100))) 
		#define LD_DATA_PORT		(*((volatile unsigned char xdata*)(0x8000))) 
		//评估板上 MCU的A8 连接到 LD芯片的AD
		//         MCU的A14 连接到 LD芯片的CSB
		//         MCU的RD、WR 连接 LD芯片的RD、WR (xdata 读写时自动产生低信号)
		//
		//0x8100的二进制是10000001 00000000		CSB=0 AD=1
		//                 ^     ^
		//0x8000的二进制是10000000 00000000		CSB=0 AD=0
		//                 ^     ^		
		void LD_WriteReg( unsigned char address, unsigned char dataout )
		{
			LD_INDEX_PORT  = address;         
			LD_DATA_PORT = dataout;          
		}
		
		unsigned char LD_ReadReg( unsigned char address )
		{
			LD_INDEX_PORT = address;         
			return (unsigned char)LD_DATA_PORT;     
		}

