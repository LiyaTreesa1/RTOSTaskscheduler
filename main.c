#include<stdio.h>
typedefstruct 
{
uint32_t *stackPtr;
uint32_t delay;
void(*taskFunc)(void);
}TCB_t;

#define MAXCOUNT 4

TCB_t tcb[MAXCOUNT];
int taskCount;
int currentTask=0;

voidRTOS_CreateTask(TCB_t *tcb, void (*func)(void), uint32_t *stack, uint32_t stackSize);
{
tcb->stackPtr=stack+stackSize;//stack is the bottom of the stack.
//stack + stackSize is the top of the stack.
tcb->delay=0
tcb->taskFunc=func;
}

voidRTOS_Schedule(void)
{
    currentTask=(currentTask+1)%taskCount; 
}

voidSysTick_Handler(void)
{
    for(int i=0;i<taskCount;i++)
    if(tcb[i].delay>0)
    {
       tcb[i].delay--;
    }
}

void Idle_Task(void)
{
    while(1)__WFI();// sleep until next interrupt
}

voidLEDtask(void)
{
 printf("LED task: toggle LED\n");
    tcb[0].delay = 5; // sleep for 5 ticks   
}

void UART_task(void)
{
 printf("UART task: toggle LED\n");
    tcb[1].delay = 3; // sleep for 5 ticks   
}

void Sensor_task(void)
{
    printf("UART task: toggle LED\n");
    tcb[2].delay = 4; // sleep for 5 ticks   
}