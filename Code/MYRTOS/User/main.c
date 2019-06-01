#include "list.h"
#include "task.h"

/*
*************************************************************************
*                              ȫ�ֱ���
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

/* ����1 */
void Task1_Entry( void *p_arg );
/* ����2 */
void Task2_Entry( void *p_arg );

extern List_t pxReadyTasksLists[ configMAX_PRIORITIES ];

int main(void)
{	
	
	//�������г�ʼ��
	prvInitialseTaskLists();
	
	//��������
	Task1_Handle = xTaskCreateStatic(
												(TaskFunction_t)Task1_Entry,//������ں���
												(char *)("Task_1"),
												(uint32_t)TASK1_STACK_SIZE,
												(void *)NULL,
												(StackType_t *)Task1Stack,
												(TCB_t *)(&Task1TCB)
											);
//��������ӵ�����������
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
													
	//�����������
  
													
													
													
}


/*
*************************************************************************
*                               ����ʵ��
*************************************************************************
*/
/* �����ʱ */
void delay (uint32_t count)
{
	for(; count!=0; count--);
}
/* ����1 */
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


/* ����2 */
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
