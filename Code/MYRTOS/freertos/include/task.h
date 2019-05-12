#ifndef INC_TASK_H
#define INC_TASK_H

#include "list.h"
#include "projdefs.h"

/*任务句柄*/
typedef void *TaskHandle_t;

/*静态任务创建方式*/
#if( configSUPPORT_STATIC_ALLOCATION == 1 )
TaskHandle_t xTaskCreateStatic(   TaskFunction_t pxTaskCode,//任务入口，即任务的函数名称
																  const char * const pcName,//任务名称，字符串形式，方便调试
																	const uint32_t ulStackDepth,//任务栈大小，单位为字
																	void * const pvParameters,//形参
																	StackType_t * const puxStackBuffer,//任务栈起始地址
																	TCB_t * const pxTaskBuffer//任务控制模块指针
															);
#endif

/*进行任务创建*/																	
static void prvInitialiseNewTask( TaskFunction_t pxTaskCode,//任务入口，即任务的函数名称
																	const char * const pcName,//任务名称，字符串形式，方便调试
																	const uint32_t ulStackDepth,//任务栈大小，单位为字
																	void * const pvParameters,
																	TaskHandle_t * const pxCreatedTask,
																	TCB_t *pxNewTCB
																);   
					
#endif /* INC_TASK_H */ 
