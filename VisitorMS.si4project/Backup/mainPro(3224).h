
#include "controlDevice.h"
#include "inputCommand.h"
#include "identityRecognition.h"
#include "menu.h"
#include "snake.h"
#include "camera.h"
#include "ftp.h"


/* 定义全局变量 */
struct controlDevice *pdeviceHead = NULL;




/* 定义mainFunctionInit函数需要的变量 */
struct controlDevice *tmp = NULL;






/**********************************************************************
 * 函数名称： findDeviceByName
 * 功能描述： 设备链表中查找结点
 * 输入参数： name - 名字，phead - 链表头结点
 * 输出参数： 无
 * 返 回 值： 返回结点指针
 * 修改日期        版本号     修改人	      修改内容
 * -----------------------------------------------
 * 2022/05/18	V1.0   杨皓清	        创建
 ***********************************************************************/
struct controlDevice *findDeviceByName(char *name, struct controlDevice *phead)
{
	struct controlDevice *tmp = phead;
	if (phead == NULL) {
		return NULL;
	} else {
		while (tmp != NULL) {
			if (strcmp(tmp->deviceName, name) == 0) {
				return tmp;
			}
			tmp = tmp->next;
		}
	}
}

/**********************************************************************
 * 函数名称： findRecognitionByName
 * 功能描述： 指令链表中查找结点
 * 输入参数： name - 名字，phead - 链表头结点
 * 输出参数： 无
 * 返 回 值： 返回结点指针
 * 修改日期        版本号     修改人	      修改内容
 * -----------------------------------------------
 * 2022/05/18	V1.0   杨皓清	        创建
 ***********************************************************************/
struct identityRecognition *findRecognitionByName(char *name, struct identityRecognition *phead)
{
	struct identityRecognition *tmp = phead;
	if (phead == NULL) {
		return NULL;
	} else {
		while (tmp != NULL) {
			if (strcmp(tmp->identityName, name) == 0) {
				return tmp;
			}
			tmp = tmp->next;
		}
	}
}

/**********************************************************************
 * 函数名称： mainFunctionProgram
 * 功能描述： 设备初始化工作
 * 输入参数： 无
 * 输出参数： 无
 * 返 回 值： 无
 * 修改日期        版本号     修改人	      修改内容
 * -----------------------------------------------
 * 2022/05/18	V1.0   杨皓清	        创建
 ***********************************************************************/
void mainFunctionInit(void)
{
	/* 1.指令工厂初始化 */
	pcommandHead = addvoiceControlToCommand(pcommandHead);
	pcommandHead = addsocketControlToCommand(pcommandHead);

	/* 2.设备控制工厂初始化 */
	pdeviceHead = addequipment1ToDevices(pdeviceHead);
	pdeviceHead = addequipment2ToDevices(pdeviceHead);
	pdeviceHead = addfireAlarmToDevices(pdeviceHead);





}


/* --------------------------------------------------------------------------------
 * 设备功能控制
 * --------------------------------------------------------------------------------
 * 2022/05/21	V1.0   杨皓清	        创建
 ---------------------------------------------------------------------------------- */

/* 设备1控制处理函数 */
void equipment1Process(void) 
{
	/* 局部变量定义 */
	int selectFunction = 0; 		   // 选择功能
	struct controlDevice *equipment1Node = NULL;

	/* 从设备链表中查找设备 */
	equipment1Node = findDeviceByName("equipment1", pdeviceHead);

	/* 初始化设备 */
	equipment1Node->deviceInit(equipment1Node);

	/* 功能选择界面打印，并完成功能选择 */
	while (selectFunction != 113) {

		/* 打印提示界面 */
		picOfEquipmentFunctionSelect();

		/* 选择功能 */
		selectFunction = getch();        
		switch (selectFunction) {
		case 49:
			equipment1Node->open(equipment1Node);
			break;
		case 50:
			equipment1Node->close(equipment1Node);
			break;
		case 51:
			equipment1Node->readStatus(equipment1Node);
			break;
		case 113:
			break;
		default:
			picOfInputError();
		}
	}
	
	return;
}


/* 设备2控制处理函数 */
void equipment2Process(void) 
{
	/* 局部变量定义 */
	int selectFunction = 0; 		   // 选择功能
	struct controlDevice *equipment2Node = NULL;

	/* 从设备链表中查找设备 */
	equipment2Node = findDeviceByName("equipment2", pdeviceHead);

	/* 初始化设备 */
	equipment2Node->deviceInit(equipment2Node);

	/* 功能选择界面打印，并完成功能选择 */
	while (selectFunction != 113) {

		/* 打印提示界面 */
		picOfEquipmentFunctionSelect();

		/* 选择功能 */
		selectFunction = getch();        
		switch (selectFunction) {
		case 49:
			equipment2Node->open(equipment2Node);
			break;
		case 50:
			equipment2Node->close(equipment2Node);
			break;
		case 51:
			equipment2Node->readStatus(equipment2Node);
			break;
		case 113:
			break;
		default:
			picOfInputError();
		}
	}
	
	return;
}

/* 设备3控制处理函数 */
void fireAlarmProcess(void) 
{
	/* 局部变量定义 */
	int selectFunction = 0; 		   // 选择功能
	struct controlDevice *fireAlarmNode = NULL;

	/* 从设备链表中查找设备 */
	fireAlarmNode = findDeviceByName("fireAlarm", pdeviceHead);

	/* 初始化设备 */
	fireAlarmNode->deviceInit(fireAlarmNode);

	/* 功能选择界面打印，并完成功能选择 */
	while (selectFunction != 113) {

		/* 打印提示界面 */
		picOfEquipmentFunctionSelect();

		/* 选择功能 */
		selectFunction = getch();        
		switch (selectFunction) {
		case 49:
			fireAlarmNode->open(fireAlarmNode);
			break;
		case 50:
			fireAlarmNode->close(fireAlarmNode);
			break;
		case 51:
			fireAlarmNode->readStatus(fireAlarmNode);
			break;
		case 113:
			break;
		default:
			picOfInputError();
		}
	}
	
	return;
}

/* 摄像头控制处理函数 */
void cameraProcess(void)
{
	/* 局部变量定义 */
	int selectFunction = 0; 		   // 选择功能

	/* 功能选择界面打印，并完成功能选择 */
	while (selectFunction != 113) {

		/* 打印提示界面 */
		picOfCameraFunctionSelect();

		/* 选择功能 */
		selectFunction = getch();        
		switch (selectFunction) {
		case 49:
			openCamera();
			break;
		case 50:
			closeCamera();
			break;
		case 113:
			break;
		default:
			picOfInputError();
		}
	}
	
	return;

}

/* 下载日志处理函数 */
void downloadLogProcess(void)
{
	/* 局部变量定义 */
	int selectFunction = 0; 		   // 选择功能

	/* 功能选择界面打印，并完成功能选择 */
	while (selectFunction != 113) {

		/* 打印提示界面 */
		picOfFtpFunctionSelect();

		/* 选择功能 */
		selectFunction = getch();        
		switch (selectFunction) {
		case 49:
			openFtp(1);
			break;
		case 50:
			openFtp(2);
			break;
		case 51:
			openFtp(2);
			break;
		case 52:
			closeFtp();
			break;
		case 113:
			break;
		default:
			picOfInputError();
		}
	}
	
	return;

}


/* --------------------------------------------------------------------------------
 * 识别功能实现
 * --------------------------------------------------------------------------------
 * 2022/05/23	V1.0   杨皓清	        创建
 ---------------------------------------------------------------------------------- */

/* 密码识别处理函数 */
void passwordRecognitionProcess(void) 
{

}

/* 人脸识别处理函数 */
void faceRecognitionProcess(void) 
{

}

/* 口令识别处理函数 */
void voiceRecognitionProcess(void) 
{

}

/* APP识别处理函数 */
void AppRecognitionProcess(void) 
{

}
















