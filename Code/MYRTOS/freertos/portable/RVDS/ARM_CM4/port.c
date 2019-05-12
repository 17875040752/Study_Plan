#include "FreeRTOS.h"
#include "task.h"
#include "ARMCM3.h"

#define portINITIAL_XPSR ( 0x01000000 )
#define portSTART_ADDRESS_MASK ( ( StackType_t ) 0xfffffffeUL )

StackType_t *pxPortInitialiseStack( StackType_t *pxTopOfStack, TaskFunction_t pxCode, void *pvParameters )
{
	/* 
	(1) �쳣����ʱ���Զ����ص�CPU�Ĵ��������� 
	(2) �����������ݣ�R0 ~ R3�����Ĵ���    R13ջָ��SP��MSP/PSP��   R14���ӽ���������ڱ�����������ַ  R15���������PC
	*/
	pxTopOfStack--;
	*pxTopOfStack = portINITIAL_XPSR;
	pxTopOfStack--;
	
	
	
	

	return 0;

}

