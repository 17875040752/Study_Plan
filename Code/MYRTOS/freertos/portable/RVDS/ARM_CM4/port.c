#include "FreeRTOS.h"
#include "task.h"
#include "ARMCM3.h"

#define portINITIAL_XPSR ( 0x01000000 )
#define portSTART_ADDRESS_MASK ( ( StackType_t ) 0xfffffffeUL )

static void prvTaskExitError( void )
{
    /* 函数停止在这里 */
    for(;;);
}

StackType_t *pxPortInitialiseStack( StackType_t *pxTopOfStack, TaskFunction_t pxCode, void *pvParameters )
{
	/* 
	(1) 异常发生时，自动加载到CPU寄存器的内容 
	(2) 主动保存内容：R0 ~ R3参数寄存器    R13栈指针SP（MSP/PSP）   R14链接结存器，用于保存主函数地址  R15程序计数器PC
	*/
	pxTopOfStack--;
	*pxTopOfStack = portINITIAL_XPSR;/* xPSR的bit24必须置1,该标志为表示：使用的是Thimb指令集 */
	pxTopOfStack--;
	(*pxTopOfStack) = ((StackType_t )pxCode) & portSTART_ADDRESS_MASK;
	pxTopOfStack--;
	*pxTopOfStack = ( StackType_t ) prvTaskExitError;	                    /* LR，函数返回地址 */
	pxTopOfStack -= 5;	/* R12, R3, R2 and R1 默认初始化为0 */
	*pxTopOfStack = ( StackType_t ) pvParameters;	                        /* R0，任务形参 */
   
    /* 异常发生时，手动加载到CPU寄存器的内容 */    
	pxTopOfStack -= 8;	/* R11, R10, R9, R8, R7, R6, R5 and R4默认初始化为0 */
		
	/* 返回栈顶指针，此时pxTopOfStack指向空闲栈 */
    return pxTopOfStack;
}
