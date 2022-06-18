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
/************************************************************************************/
//	nAsrStatus 用来在main主程序中表示程序运行的状态，不是LD3320芯片内部的状态寄存器
//	LD_ASR_NONE:		表示没有在作ASR识别
//	LD_ASR_RUNING：		表示LD3320正在作ASR识别中
//	LD_ASR_FOUNDOK:		表示一次识别流程结束后，有一个识别结果
//	LD_ASR_FOUNDZERO:	表示一次识别流程结束后，没有识别结果
//	LD_ASR_ERROR:		表示一次识别流程中LD3320芯片内部出现不正确的状态
/***********************************************************************************/
uint8 idata nAsrStatus=0;	
void MCU_init(); 
void ProcessInt0(); //识别处理函数
void delay(unsigned long uldata);
void User_handle(uint8 dat);//用户执行操作函数
void Delay200ms();
void Led_test(void);//单片机工作指示
uint8_t G0_flag=DISABLE;//运行标志，ENABLE:运行。DISABLE:禁止运行 
sbit LED=P4^2;//信号指示灯

/***********************************************************
* 名    称： void  main(void)
* 功    能： 主函数	程序入口
* 入口参数：  
* 出口参数：
* 说    明： 					 
* 调用方法： 
**********************************************************/ 
void  main(void)
{
	uint8 idata nAsrRes;
	uint8 i=0;
	Led_test();
	MCU_init();
	LD_Reset();
	UartIni(); /*串口初始化*/
	nAsrStatus = LD_ASR_NONE;		//	初始状态：没有在作ASR
	
	#ifdef TEST	
  PrintCom("一级口令：小杰\r\n"); /*text.....*/
	PrintCom("二级口令：1、打开设备一\r\n"); /*text.....*/
	PrintCom("	2、关闭设备一\r\n"); /*text.....*/
	PrintCom("	3、打开设备二\r\n"); /*text.....*/
	PrintCom("	4、关闭设备二\r\n"); /*text.....*/
	PrintCom("  5、芝麻开门\r\n"); /*text.....*/
	PrintCom("	6、身份验证\r\n"); /*text.....*/
	PrintCom("	7、退出\r\n"); /*text.....*/
	#endif

	while(1)
	{
		switch(nAsrStatus)
		{
			case LD_ASR_RUNING:
			case LD_ASR_ERROR:		
				break;
			case LD_ASR_NONE:
			{
				nAsrStatus=LD_ASR_RUNING;
				if (RunASR()==0)	/*	启动一次ASR识别流程：ASR初始化，ASR添加关键词语，启动ASR运算*/
				{
					nAsrStatus = LD_ASR_ERROR;
				}
				break;
			}
			case LD_ASR_FOUNDOK: /*	一次ASR识别流程结束，去取ASR识别结果*/
			{				
				nAsrRes = LD_GetResult();		/*获取结果*/
				User_handle(nAsrRes);//用户执行函数 
				nAsrStatus = LD_ASR_NONE;
				break;
			}
			case LD_ASR_FOUNDZERO:
			default:
			{
				nAsrStatus = LD_ASR_NONE;
				break;
			}
		}// switch	 			
	}// while

}
/***********************************************************
* 名    称： 	 LED灯测试
* 功    能： 单片机是否工作指示
* 入口参数： 无 
* 出口参数：无
* 说    明： 					 
**********************************************************/
void Led_test(void)
{
	LED=~ LED;
	Delay200ms();
	LED=~ LED;
	Delay200ms();
	LED=~ LED;
	Delay200ms();
	LED=~ LED;
	Delay200ms();
	LED=~ LED;
	Delay200ms();
	LED=~ LED;
}
/***********************************************************
* 名    称： void MCU_init()
* 功    能： 单片机初始化
* 入口参数：  
* 出口参数：
* 说    明： 					 
* 调用方法： 
**********************************************************/ 
void MCU_init()
{
	P0 = 0xff;
	P1 = 0xff;
	P2 = 0xff;
	P3 = 0xff;
	P4 = 0xff;
	

	LD_MODE = 0;		//	设置MD管脚为低，并行模式读写
	IE0=1;
	EX0=1;
	EA=1;
}
/***********************************************************
* 名    称：	延时函数
* 功    能：
* 入口参数：  
* 出口参数：
* 说    明： 					 
* 调用方法： 
**********************************************************/ 
void Delay200us()		//@22.1184MHz
{
	unsigned char i, j;
	_nop_();
	_nop_();
	i = 5;
	j = 73;
	do
	{
		while (--j);
	} while (--i);
}

void  delay(unsigned long uldata)
{
	unsigned int j  =  0;
	unsigned int g  =  0;
	while(uldata--)
	Delay200us();
}

void Delay200ms()		//@22.1184MHz
{
	unsigned char i, j, k;

	i = 17;
	j = 208;
	k = 27;
	do
	{
		do
		{
			while (--k);
		} while (--j);
	} while (--i);
}

/***********************************************************
* 名    称： 中断处理函数
* 功    能：
* 入口参数：  
* 出口参数：
* 说    明： 					 
* 调用方法： 
**********************************************************/ 
void ExtInt0Handler(void) interrupt 0  
{ 	
	ProcessInt0();				
}
/***********************************************************
* 名    称：用户执行函数 
* 功    能：识别成功后，执行动作可在此进行修改 
* 入口参数： 无 
* 出口参数：无
* 说    明： 					 
**********************************************************/
void 	User_handle(uint8 dat)
{
     //UARTSendByte(dat);//串口识别码（十六进制）
		 if(0==dat)
		 {
		  	G0_flag=ENABLE;
			LED=0;
			PrintCom("收到\r\n"); /*text.....*/
		 }
		 else if(ENABLE==G0_flag)
		 {	
		 		G0_flag=DISABLE;
				LED=1;

			 switch(dat)		   /*对结果执行相关操作,客户可删除Printcom 串口输出语句替换为其他需要控制的代码*/
			  {
				  case CODE_DMCS:			/*命令“测试”*/
						PrintCom("open1"); /*text.....*/
													 break;
					case CODE_KFBYZ:	 /*命令“全开”*/
						PrintCom("close1"); /*text.....*/
													 break;
					case CODE_KD:		/*命令“复位”*/				
						PrintCom("open2"); /*text.....*/
													break;
					case CODE_GD:		/*命令“复位”*/				
						PrintCom("close2"); /*text.....*/
													break;
					case CODE_BJ:		/*命令“复位”*/				
						PrintCom("123312"); /*text.....*/
													break;
					case CODE_SH:		/*命令“复位”*/				
						PrintCom("123312"); /*text.....*/
													break;
					case CODE_GZ:		/*命令“复位”*/				
						PrintCom("q"); /*text.....*/
													break;																											
							default:PrintCom("请重新识别发口令\r\n"); /*text.....*/break;
				}	

#if 0
			 switch(dat)		   /*对结果执行相关操作,客户可删除Printcom 串口输出语句替换为其他需要控制的代码*/
			  {
				  case CODE_DMCS:			/*命令“测试”*/
						PrintCom("“打开设备一”命令识别成功\r\n"); /*text.....*/
													 break;
					case CODE_KFBYZ:	 /*命令“全开”*/
						PrintCom("“关闭设备一”命令识别成功\r\n"); /*text.....*/
													 break;
					case CODE_KD:		/*命令“复位”*/				
						PrintCom("“打开设备二”命令识别成功\r\n"); /*text.....*/
													break;
					case CODE_GD:		/*命令“复位”*/				
						PrintCom("“关闭设备二”命令识别成功\r\n"); /*text.....*/
													break;
					case CODE_BJ:		/*命令“复位”*/				
						PrintCom("“芝麻开门”命令识别成功\r\n"); /*text.....*/
													break;
					case CODE_SH:		/*命令“复位”*/				
						PrintCom("“身份验证”命令识别成功\r\n"); /*text.....*/
													break;
					case CODE_GZ:		/*命令“复位”*/				
						PrintCom("“退出”命令识别成功\r\n"); /*text.....*/
													break;																											
							default:PrintCom("请重新识别发口令\r\n"); /*text.....*/break;
				}
#endif
	
			}
			else 	
			{
				PrintCom("请说出一级口令\r\n"); /*text.....*/	
			}
}	 
