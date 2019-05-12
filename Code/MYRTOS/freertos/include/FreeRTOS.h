#ifndef INC_FREERTOS_H
#define INC_FREERTOS_H

#include "FreeRTOSConfig.h"
#include "portable.h"

/* 节点结构体定义 */
struct xLIST_ITEM
{
	TickType_t xItemValue;             /* 辅助值，用于帮助节点做顺序排列 */			
	struct xLIST_ITEM *  pxNext;       /* 指向链表下一个节点 */		
	struct xLIST_ITEM *  pxPrevious;   /* 指向链表前一个节点 */	
	void * pvOwner;					   /* 指向拥有该节点的内核对象，通常是TCB */
	void *  pvContainer;		       /* 指向该节点所在的链表 */
};
typedef struct xLIST_ITEM ListItem_t;  /* 节点数据类型重定义 */



/* mini节点结构体定义，作为双向链表的结尾
   因为双向链表是首尾相连的，头即是尾，尾即是头 */
struct xMINI_LIST_ITEM
{
	TickType_t xItemValue;                      /* 辅助值，用于帮助节点做升序排列 */
	struct xLIST_ITEM *  pxNext;                /* 指向链表下一个节点 */
	struct xLIST_ITEM *  pxPrevious;            /* 指向链表前一个节点 */
};
typedef struct xMINI_LIST_ITEM MiniListItem_t;  /* 最小节点数据类型重定义 */


/* 链表结构体定义 */
typedef struct xLIST
{
	UBaseType_t uxNumberOfItems;    /* 链表节点计数器 */
	ListItem_t *  pxIndex;			/* 链表节点索引指针 */
	MiniListItem_t xListEnd;		/* 链表最后一个节点 */
} List_t;


typedef struct tskTaskControlBlock
{
	volatile StackType_t    *pxTopOfStack;    /* 栈顶 */
	ListItem_t			    xStateListItem;   /* 任务节点 */
  StackType_t             *pxStack;         /* 任务栈起始地址 */                                  
	char                    pcTaskName[ configMAX_TASK_NAME_LEN ];  /* 任务名称，字符串形式 */
} tskTCB;
typedef tskTCB TCB_t;


#endif /* INC_FREERTOS_H */
