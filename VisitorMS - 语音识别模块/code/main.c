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
 *  �������ƣ�YS-V0.7����ʶ��ģ����������
 *	CPU: STC11L08XE
 *	����22.1184MHZ
 *	�����ʣ�9600 bit/S
 *	���ײ�Ʒ��Ϣ��YS-V0.7����ʶ�𿪷���
 *  ˵��������ģʽ�� ��ÿ��ʶ��ʱ����Ҫ˵��С�ܡ�������� �����ܹ�������һ����ʶ��
 *
 *********************************************************************************************/

#include "config.h"
/************************************************************************************/
//	nAsrStatus ������main�������б�ʾ�������е�״̬������LD3320оƬ�ڲ���״̬�Ĵ���
//	LD_ASR_NONE:		��ʾû������ASRʶ��
//	LD_ASR_RUNING��		��ʾLD3320������ASRʶ����
//	LD_ASR_FOUNDOK:		��ʾһ��ʶ�����̽�������һ��ʶ����
//	LD_ASR_FOUNDZERO:	��ʾһ��ʶ�����̽�����û��ʶ����
//	LD_ASR_ERROR:		��ʾһ��ʶ��������LD3320оƬ�ڲ����ֲ���ȷ��״̬
/***********************************************************************************/
uint8 idata nAsrStatus=0;	
void MCU_init(); 
void ProcessInt0(); //ʶ������
void delay(unsigned long uldata);
void User_handle(uint8 dat);//�û�ִ�в�������
void Delay200ms();
void Led_test(void);//��Ƭ������ָʾ
uint8_t G0_flag=DISABLE;//���б�־��ENABLE:���С�DISABLE:��ֹ���� 
sbit LED=P4^2;//�ź�ָʾ��

/***********************************************************
* ��    �ƣ� void  main(void)
* ��    �ܣ� ������	�������
* ��ڲ�����  
* ���ڲ�����
* ˵    ���� 					 
* ���÷����� 
**********************************************************/ 
void  main(void)
{
	uint8 idata nAsrRes;
	uint8 i=0;
	Led_test();
	MCU_init();
	LD_Reset();
	UartIni(); /*���ڳ�ʼ��*/
	nAsrStatus = LD_ASR_NONE;		//	��ʼ״̬��û������ASR
	
	#ifdef TEST	
  PrintCom("һ�����С��\r\n"); /*text.....*/
	PrintCom("�������1�����豸һ\r\n"); /*text.....*/
	PrintCom("	2���ر��豸һ\r\n"); /*text.....*/
	PrintCom("	3�����豸��\r\n"); /*text.....*/
	PrintCom("	4���ر��豸��\r\n"); /*text.....*/
	PrintCom("  5��֥�鿪��\r\n"); /*text.....*/
	PrintCom("	6�������֤\r\n"); /*text.....*/
	PrintCom("	7���˳�\r\n"); /*text.....*/
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
				if (RunASR()==0)	/*	����һ��ASRʶ�����̣�ASR��ʼ����ASR��ӹؼ��������ASR����*/
				{
					nAsrStatus = LD_ASR_ERROR;
				}
				break;
			}
			case LD_ASR_FOUNDOK: /*	һ��ASRʶ�����̽�����ȥȡASRʶ����*/
			{				
				nAsrRes = LD_GetResult();		/*��ȡ���*/
				User_handle(nAsrRes);//�û�ִ�к��� 
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
* ��    �ƣ� 	 LED�Ʋ���
* ��    �ܣ� ��Ƭ���Ƿ���ָʾ
* ��ڲ����� �� 
* ���ڲ�������
* ˵    ���� 					 
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
* ��    �ƣ� void MCU_init()
* ��    �ܣ� ��Ƭ����ʼ��
* ��ڲ�����  
* ���ڲ�����
* ˵    ���� 					 
* ���÷����� 
**********************************************************/ 
void MCU_init()
{
	P0 = 0xff;
	P1 = 0xff;
	P2 = 0xff;
	P3 = 0xff;
	P4 = 0xff;
	

	LD_MODE = 0;		//	����MD�ܽ�Ϊ�ͣ�����ģʽ��д
	IE0=1;
	EX0=1;
	EA=1;
}
/***********************************************************
* ��    �ƣ�	��ʱ����
* ��    �ܣ�
* ��ڲ�����  
* ���ڲ�����
* ˵    ���� 					 
* ���÷����� 
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
* ��    �ƣ� �жϴ�����
* ��    �ܣ�
* ��ڲ�����  
* ���ڲ�����
* ˵    ���� 					 
* ���÷����� 
**********************************************************/ 
void ExtInt0Handler(void) interrupt 0  
{ 	
	ProcessInt0();				
}
/***********************************************************
* ��    �ƣ��û�ִ�к��� 
* ��    �ܣ�ʶ��ɹ���ִ�ж������ڴ˽����޸� 
* ��ڲ����� �� 
* ���ڲ�������
* ˵    ���� 					 
**********************************************************/
void 	User_handle(uint8 dat)
{
     //UARTSendByte(dat);//����ʶ���루ʮ�����ƣ�
		 if(0==dat)
		 {
		  	G0_flag=ENABLE;
			LED=0;
			PrintCom("�յ�\r\n"); /*text.....*/
		 }
		 else if(ENABLE==G0_flag)
		 {	
		 		G0_flag=DISABLE;
				LED=1;

			 switch(dat)		   /*�Խ��ִ����ز���,�ͻ���ɾ��Printcom �����������滻Ϊ������Ҫ���ƵĴ���*/
			  {
				  case CODE_DMCS:			/*������ԡ�*/
						PrintCom("open1"); /*text.....*/
													 break;
					case CODE_KFBYZ:	 /*���ȫ����*/
						PrintCom("close1"); /*text.....*/
													 break;
					case CODE_KD:		/*�����λ��*/				
						PrintCom("open2"); /*text.....*/
													break;
					case CODE_GD:		/*�����λ��*/				
						PrintCom("close2"); /*text.....*/
													break;
					case CODE_BJ:		/*�����λ��*/				
						PrintCom("123312"); /*text.....*/
													break;
					case CODE_SH:		/*�����λ��*/				
						PrintCom("123312"); /*text.....*/
													break;
					case CODE_GZ:		/*�����λ��*/				
						PrintCom("q"); /*text.....*/
													break;																											
							default:PrintCom("������ʶ�𷢿���\r\n"); /*text.....*/break;
				}	

#if 0
			 switch(dat)		   /*�Խ��ִ����ز���,�ͻ���ɾ��Printcom �����������滻Ϊ������Ҫ���ƵĴ���*/
			  {
				  case CODE_DMCS:			/*������ԡ�*/
						PrintCom("�����豸һ������ʶ��ɹ�\r\n"); /*text.....*/
													 break;
					case CODE_KFBYZ:	 /*���ȫ����*/
						PrintCom("���ر��豸һ������ʶ��ɹ�\r\n"); /*text.....*/
													 break;
					case CODE_KD:		/*�����λ��*/				
						PrintCom("�����豸��������ʶ��ɹ�\r\n"); /*text.....*/
													break;
					case CODE_GD:		/*�����λ��*/				
						PrintCom("���ر��豸��������ʶ��ɹ�\r\n"); /*text.....*/
													break;
					case CODE_BJ:		/*�����λ��*/				
						PrintCom("��֥�鿪�š�����ʶ��ɹ�\r\n"); /*text.....*/
													break;
					case CODE_SH:		/*�����λ��*/				
						PrintCom("�������֤������ʶ��ɹ�\r\n"); /*text.....*/
													break;
					case CODE_GZ:		/*�����λ��*/				
						PrintCom("���˳�������ʶ��ɹ�\r\n"); /*text.....*/
													break;																											
							default:PrintCom("������ʶ�𷢿���\r\n"); /*text.....*/break;
				}
#endif
	
			}
			else 	
			{
				PrintCom("��˵��һ������\r\n"); /*text.....*/	
			}
}	 
