#include "task.h"
#include "FreeRTOS.h"

/* ��������б� */
List_t pxReadyTasksLists[ configMAX_PRIORITIES ];
/* ��ǰ�������е������������ƿ�ָ�룬Ĭ�ϳ�ʼ��ΪNULL */
TCB_t * volatile pxCurrentTCB = NULL;

extern StackType_t *pxPortInitialiseStack( StackType_t *pxTopOfStack, TaskFunction_t pxCode, void *pvParameters );
extern TCB_t Task1TCB;
extern TCB_t Task2TCB;

TaskHandle_t xTaskCreateStatic(
								TaskFunction_t pxTaskCode,
								const char * const pcName,//�������ƣ��ַ�����ʽ���������
								const uint32_t ulStackDepth,//����ջ��С����λΪ��
								void * const pvParameters,//�β�
								StackType_t * const puxStackBuffer,//����ջ��ʼ��ַ
								TCB_t * const pxTaskBuffer//�������ģ��ָ��
															)
{
	TCB_t *pxNewTCB;//������ƽṹ
	TaskHandle_t xReturn;//���ؽ��
	
	if( pxTaskBuffer != NULL && puxStackBuffer != NULL )
	{	
		pxNewTCB = (TCB_t *) pxTaskBuffer;//���������ģ�飬Linux�еķ���ʵ��дʱ��������
		pxNewTCB->pxStack = (StackType_t *) puxStackBuffer;//����ջ��ʼ��ַ
		/*��������*/
		prvInitialiseNewTask(pxTaskCode,pcName,ulStackDepth,pvParameters,&xReturn,pxNewTCB);
	}
	
	return xReturn;
}


/*��������*/
static void prvInitialiseNewTask( 
																	TaskFunction_t pxTaskCode,//������ڣ�������ĺ�������
																	const char * const pcName,//�������ƣ��ַ�����ʽ���������
																	const uint32_t ulStackDepth,//����ջ��С����λΪ��
																	void * const pvParameters,
																	TaskHandle_t * const pxCreatedTask,
																	TCB_t *pxNewTCB
																)
{
	StackType_t *pxTopOfStack;
	UBaseType_t x;
	
	/* ��ȡջ����ַ */
	pxTopOfStack = pxNewTCB->pxStack + ulStackDepth - (uint32_t)1;
	/* ������ 8 �ֽڶ��� */
	 pxTopOfStack = ( StackType_t * ) ( ( ( uint32_t ) pxTopOfStack ) & ( ~( ( uint32_t ) 0x0007 ) ) );
	/* ����������ִ洢�� TCB �� */
	for ( x = ( UBaseType_t ) 0; x < ( UBaseType_t ) configMAX_TASK_NAME_LEN; x++ )
  {
		if(*(pcName + x))
		  *(pxNewTCB->pcTaskName + x) = *(pcName + x);
	}
	*(pxNewTCB->pcTaskName + x) = '\0';
	
	/*ջ�ռ䴴��*/
	pxPortInitialiseStack(pxTopOfStack,pxTaskCode,pvParameters);
	
	/*�����ָ������ģ��*/
	if ((TaskHandle_t)pxCreatedTask != NULL)
		*pxCreatedTask = (TaskHandle_t) pxNewTCB;
}

//��������
void prvInitialseTaskLists(void)
{
	UBaseType_t uxPriority;
	for(uxPriority = (UBaseType_t) 0U;uxPriority < (UBaseType_t) configMAX_PRIORITIES; uxPriority++)
	{
		vListInitialise(&(pxReadyTasksLists[uxPriority]));
	}
}

//�������
void vTaskStartScheduler(void)
{
	//�ֶ���������1
	pxCurrentTCB = &Task1TCB;
	    /* ���������� */
   // if( xPortStartScheduler() != pdFALSE );
	
	
}

