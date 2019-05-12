#ifndef INC_TASK_H
#define INC_TASK_H

#include "list.h"
#include "projdefs.h"

/*������*/
typedef void *TaskHandle_t;

/*��̬���񴴽���ʽ*/
#if( configSUPPORT_STATIC_ALLOCATION == 1 )
TaskHandle_t xTaskCreateStatic(   TaskFunction_t pxTaskCode,//������ڣ�������ĺ�������
																  const char * const pcName,//�������ƣ��ַ�����ʽ���������
																	const uint32_t ulStackDepth,//����ջ��С����λΪ��
																	void * const pvParameters,//�β�
																	StackType_t * const puxStackBuffer,//����ջ��ʼ��ַ
																	TCB_t * const pxTaskBuffer//�������ģ��ָ��
															);
#endif

/*�������񴴽�*/																	
static void prvInitialiseNewTask( TaskFunction_t pxTaskCode,//������ڣ�������ĺ�������
																	const char * const pcName,//�������ƣ��ַ�����ʽ���������
																	const uint32_t ulStackDepth,//����ջ��С����λΪ��
																	void * const pvParameters,
																	TaskHandle_t * const pxCreatedTask,
																	TCB_t *pxNewTCB
																);   
					
#endif /* INC_TASK_H */ 
