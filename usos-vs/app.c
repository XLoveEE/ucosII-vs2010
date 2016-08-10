#include "includes.h"


#define  TASK_STK_SIZE    128

OS_STK        AppStk_one[TASK_STK_SIZE];
OS_STK        AppStk_two[TASK_STK_SIZE];
OS_STK        AppStk_three[TASK_STK_SIZE];




static void App_one(void *p_arg);
static void App_two(void *p_arg);
static void app_3(void *p_arg);

static void output(char *info,OS_MEM *p);
OS_MEM *mem_p;

void *ptr;

void main(int argc, char *argv[])
{
    OSInit();                              /* Initialize "uC/OS-II"*/
	ptr=malloc(10*1024);

	OSTaskCreate(App_one,NULL,&AppStk_one[TASK_STK_SIZE-1],10);
	OSTaskCreate(App_two,NULL,&AppStk_two[TASK_STK_SIZE-1],20);
	OSTaskCreate(app_3,NULL,&AppStk_three[TASK_STK_SIZE-1],30);
    OSStart();                             /* Start multitasking */
}


void App_one(void *p_arg)
{
	INT8U err;
	INT8U string[]="test memory";
	p_arg = p_arg;

	mem_p=OSMemCreate (ptr, 10, 1024, &err);
	OSMemNameSet (mem_p, string, &err);	
//	output("after create:",mem_p);

	OSTimeDlyHMSM(0, 0, 0, 5);
//	output("\nafter get twice:",mem_p);
	while(1)
	{
		printf("1234567\n");
		OSTimeDlyHMSM(0, 0, 4, 0);
	}

	OSTimeDlyHMSM(0, 0, 2, 0);
//	output("\nafter release one:",mem_p);

}

void App_two(void *p_arg)
{

	INT8U err;
	void *ptr[10];
	p_arg = p_arg;

	printf("\nfirst get:\n");
//	ptr[0]=OSMemGet (mem_p, &err);
//	printf("ptr[0]=%p\n",ptr[0]);
	OSTimeDlyHMSM(0, 0, 0, 3);

	printf("second get:\n");
//	ptr[1]=OSMemGet (mem_p, &err);
//	printf("ptr[1]=%p\n",ptr[1]);

//	OSTimeDlyHMSM(0, 0, 3, 0);
//	OSMemPut (mem_p, ptr[1]);
}

void app_3(void *p_arg)
{
	
   p_arg = p_arg;
   while(1)
   {
	   printf("abcdefgh\n");
       OSTimeDlyHMSM(0, 0, 4, 0);
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