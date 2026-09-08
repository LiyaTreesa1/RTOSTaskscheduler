#include<stdio.h>
#include <stdint.h>
#define MAXCOUNT 4
#define uint32_t unsigned int
typedef struct 
{
uint32_t *stackPtr;
uint32_t delay;
void(*taskFunc)(void);
}TCB_t;


TCB_t tcb[MAXCOUNT];
int taskCount=4;
int currentTask=0;

void RTOS_CreateTask(TCB_t *tcb, void (*func)(void), uint32_t *stack, uint32_t stackSize)
{
tcb->stackPtr=stack+stackSize;//stack is the bottom of the stack.
//stack + stackSize is the top of the stack.
tcb->delay=0;
tcb->taskFunc=func;
}

void RTOS_Schedule(void)
{
    currentTask=(currentTask+1)%taskCount; 
}

void SysTick_Handler(void)
{
    for(int i=0;i<taskCount;i++)
    if(tcb[i].delay>0)
    {
       tcb[i].delay--;
    }
}

void Idle_Task(void)
{
    while(1)
    {

    }
}

void LEDtask(void)
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
int main()
{
    static uint32_t stack_LED[128];
    static uint32_t stack_idle[128];
    static uint32_t stack_UART[128];
    static uint32_t stack_sensor[128];
    RTOS_CreateTask(&tcb[0], LEDtask, stack_LED, 128);
    RTOS_CreateTask(&tcb[1], UART_task, stack_UART, 128);
    RTOS_CreateTask(&tcb[2], Sensor_task, stack_sensor, 128);
    RTOS_CreateTask(&tcb[3], Idle_Task, stack_idle, 128);
    while (1)
    {
    SysTick_Handler();
    if (tcb[currentTask].delay == 0)
        {
            tcb[currentTask].taskFunc();
        }
        RTOS_Schedule();
    }
 
  
}