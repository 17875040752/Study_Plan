#include "FreeRTOS.h"
#include "task.h"
#include "ARMCM3.h"

#define portINITIAL_XPSR ( 0x01000000 )
#define portSTART_ADDRESS_MASK ( ( StackType_t ) 0xfffffffeUL )

StackType_t *pxPortInitialiseStack( StackType_t *pxTopOfStack, TaskFunction_t pxCode, void *pvParameters )
{
	/* 
	(1) 异常发生时，自动加载到CPU寄存器的内容 
	(2) 主动保存内容：R0 ~ R3参数寄存器    R13栈指针SP（MSP/PSP）   R14链接结存器，用于保存主函数地址  R15程序计数器PC
	*/
	pxTopOfStack--;
	*pxTopOfStack = portINITIAL_XPSR;
	pxTopOfStack--;
	
	
	
	

	return 0;

}

