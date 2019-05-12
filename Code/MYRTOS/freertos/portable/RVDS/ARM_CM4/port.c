#include "FreeRTOS.h"
#include "task.h"
#include "ARMCM3.h"

#define portINITIAL_XPSR ( 0x01000000 )
#define portSTART_ADDRESS_MASK ( ( StackType_t ) 0xfffffffeUL )

static void prvTaskExitError( void )
{
    /* ����ֹͣ������ */
    for(;;);
}

StackType_t *pxPortInitialiseStack( StackType_t *pxTopOfStack, TaskFunction_t pxCode, void *pvParameters )
{
	/* 
	(1) �쳣����ʱ���Զ����ص�CPU�Ĵ��������� 
	(2) �����������ݣ�R0 ~ R3�����Ĵ���    R13ջָ��SP��MSP/PSP��   R14���ӽ���������ڱ�����������ַ  R15���������PC
	*/
	pxTopOfStack--;
	*pxTopOfStack = portINITIAL_XPSR;/* xPSR��bit24������1,�ñ�־Ϊ��ʾ��ʹ�õ���Thimbָ� */
	pxTopOfStack--;
	(*pxTopOfStack) = ((StackType_t )pxCode) & portSTART_ADDRESS_MASK;
	pxTopOfStack--;
	*pxTopOfStack = ( StackType_t ) prvTaskExitError;	                    /* LR���������ص�ַ */
	pxTopOfStack -= 5;	/* R12, R3, R2 and R1 Ĭ�ϳ�ʼ��Ϊ0 */
	*pxTopOfStack = ( StackType_t ) pvParameters;	                        /* R0�������β� */
   
    /* �쳣����ʱ���ֶ����ص�CPU�Ĵ��������� */    
	pxTopOfStack -= 8;	/* R11, R10, R9, R8, R7, R6, R5 and R4Ĭ�ϳ�ʼ��Ϊ0 */
		
	/* ����ջ��ָ�룬��ʱpxTopOfStackָ�����ջ */
    return pxTopOfStack;
}
