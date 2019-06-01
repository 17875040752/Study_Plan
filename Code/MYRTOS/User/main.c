#include "list.h"
#include "task.h"

/*
*************************************************************************
*                              全局变量
*************************************************************************
*/
portCHAR flag1;
portCHAR flag2;

TaskHandle_t Task1_Handle;
#define TASK1_STACK_SIZE                    128
StackType_t Task1Stack[TASK1_STACK_SIZE];
TCB_t Task1TCB;

TaskHandle_t Task2_Handle;
#define TASK2_STACK_SIZE                    128
StackType_t Task2Stack[TASK2_STACK_SIZE];
TCB_t Task2TCB;

/* 任务1 */
void Task1_Entry( void *p_arg );
/* 任务2 */
void Task2_Entry( void *p_arg );

extern List_t pxReadyTasksLists[ configMAX_PRIORITIES ];

int main(void)
{	
	
	//就绪队列初始化
	prvInitialseTaskLists();
	
	//创建任务
	Task1_Handle = xTaskCreateStatic(
												(TaskFunction_t)Task1_Entry,//任务入口函数
												(char *)("Task_1"),
												(uint32_t)TASK1_STACK_SIZE,
												(void *)NULL,
												(StackType_t *)Task1Stack,
												(TCB_t *)(&Task1TCB)
											);
//将任务添加到就绪队列中
  vListInsertEnd(&pxReadyTasksLists[1], &( ((TCB_t *)(&Task1TCB))->xStateListItem ));
												
	Task2_Handle = xTaskCreateStatic(
													(TaskFunction_t)Task2_Entry,
													(char *)("Task_2"),
													(uint32_t)TASK2_STACK_SIZE,
													(void *)NULL,
													(StackType_t *)Task2Stack,
													(TCB_t *)(&Task2TCB)
												);
  vListInsertEnd(&pxReadyTasksLists[2],&( ((TCB_t *)(&Task1TCB))->xStateListItem ));
													
	//启动任务管理
  
													
													
													
}


/*
*************************************************************************
*                               函数实现
*************************************************************************
*/
/* 软件延时 */
void delay (uint32_t count)
{
	for(; count!=0; count--);
}
/* 任务1 */
void Task1_Entry( void *p_arg )
{
	for( ;; )
	{
		flag1 = 1;
		delay( 100 );		
		flag1 = 0;
		delay( 100 );
	}
}


/* 任务2 */
void Task2_Entry( void *p_arg )
{
	for( ;; )
	{
		flag2 = 1;
		delay( 100 );		
		flag2 = 0;
		delay( 100 );
	}
}
