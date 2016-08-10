#include "includes.h"

#define  TASK_STK_SIZE    128

OS_STK        AppStk_one[TASK_STK_SIZE];
OS_STK        AppStk_two[TASK_STK_SIZE];
OS_STK        AppStk_three[TASK_STK_SIZE];

static void App_one(void *p_arg);
static void App_two(void *p_arg);

static void output(char *info,OS_MEM *p);
OS_MEM *mem_p;

void *ptr;

void main(int argc, char *argv[])
{
    OSInit();                              /* Initialize "uC/OS-II"*/
	OSTaskCreate(App_one,NULL,&AppStk_one[TASK_STK_SIZE-1],10);
	OSTaskCreate(App_two,NULL,&AppStk_two[TASK_STK_SIZE-1],20);
    OSStart();                             /* Start multitasking */
}


void App_one(void *p_arg)
{
	INT32U count = 0;
	while(1){
	printf("Task one Count is %d\n",count);
	count++;
	OSTimeDlyHMSM(0,0,5,0);	
	}

	
}

void App_two(void *p_arg)
{
	INT32U count = 100;
	while(1){
	printf("Task two Count is %d\n",count);
	count++;
	OSTimeDlyHMSM(0,0,1,0);	
	}
}

void output(char *info,OS_MEM *p)
{
	printf("%s\n",info);
	printf("OSMemAddr=%p\n",p->OSMemAddr);
	printf("OSMemFreeList=%p\n",p->OSMemFreeList);
	printf("OSMemBlkSize=%d\n",p->OSMemBlkSize);
	printf("OSMemName=%s\n",p->OSMemName);
	printf("OSMemNFree=%d\n",p->OSMemNFree);
	printf("OSMemNBlks=%d\n",p->OSMemNBlks);
}