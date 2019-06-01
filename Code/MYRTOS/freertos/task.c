#include "task.h"
#include "FreeRTOS.h"

/* 任务就绪列表 */
List_t pxReadyTasksLists[ configMAX_PRIORITIES ];
/* 当前正在运行的任务的任务控制块指针，默认初始化为NULL */
TCB_t * volatile pxCurrentTCB = NULL;

extern StackType_t *pxPortInitialiseStack( StackType_t *pxTopOfStack, TaskFunction_t pxCode, void *pvParameters );
extern TCB_t Task1TCB;
extern TCB_t Task2TCB;

TaskHandle_t xTaskCreateStatic(
								TaskFunction_t pxTaskCode,
								const char * const pcName,//任务名称，字符串形式，方便调试
								const uint32_t ulStackDepth,//任务栈大小，单位为字
								void * const pvParameters,//形参
								StackType_t * const puxStackBuffer,//任务栈起始地址
								TCB_t * const pxTaskBuffer//任务控制模块指针
															)
{
	TCB_t *pxNewTCB;//任务控制结构
	TaskHandle_t xReturn;//返回结果
	
	if( pxTaskBuffer != NULL && puxStackBuffer != NULL )
	{	
		pxNewTCB = (TCB_t *) pxTaskBuffer;//传入的任务模块，Linux中的方便实现写时拷贝技术
		pxNewTCB->pxStack = (StackType_t *) puxStackBuffer;//任务栈起始地址
		/*创建任务*/
		prvInitialiseNewTask(pxTaskCode,pcName,ulStackDepth,pvParameters,&xReturn,pxNewTCB);
	}
	
	return xReturn;
}


/*创建任务*/
static void prvInitialiseNewTask( 
																	TaskFunction_t pxTaskCode,//任务入口，即任务的函数名称
																	const char * const pcName,//任务名称，字符串形式，方便调试
																	const uint32_t ulStackDepth,//任务栈大小，单位为字
																	void * const pvParameters,
																	TaskHandle_t * const pxCreatedTask,
																	TCB_t *pxNewTCB
																)
{
	StackType_t *pxTopOfStack;
	UBaseType_t x;
	
	/* 获取栈顶地址 */
	pxTopOfStack = pxNewTCB->pxStack + ulStackDepth - (uint32_t)1;
	/* 向下做 8 字节对齐 */
	 pxTopOfStack = ( StackType_t * ) ( ( ( uint32_t ) pxTopOfStack ) & ( ~( ( uint32_t ) 0x0007 ) ) );
	/* 将任务的名字存储在 TCB 中 */
	for ( x = ( UBaseType_t ) 0; x < ( UBaseType_t ) configMAX_TASK_NAME_LEN; x++ )
  {
		if(*(pcName + x))
		  *(pxNewTCB->pcTaskName + x) = *(pcName + x);
	}
	*(pxNewTCB->pcTaskName + x) = '\0';
	
	/*栈空间创建*/
	pxPortInitialiseStack(pxTopOfStack,pxTaskCode,pvParameters);
	
	/*将句柄指向任务模块*/
	if ((TaskHandle_t)pxCreatedTask != NULL)
		*pxCreatedTask = (TaskHandle_t) pxNewTCB;
}

//就绪队列
void prvInitialseTaskLists(void)
{
	UBaseType_t uxPriority;
	for(uxPriority = (UBaseType_t) 0U;uxPriority < (UBaseType_t) configMAX_PRIORITIES; uxPriority++)
	{
		vListInitialise(&(pxReadyTasksLists[uxPriority]));
	}
}

//任务调度
void vTaskStartScheduler(void)
{
	//手动启用任务1
	pxCurrentTCB = &Task1TCB;
	    /* 启动调度器 */
   // if( xPortStartScheduler() != pdFALSE );
	
	
}

