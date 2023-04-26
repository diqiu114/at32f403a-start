/*
 * Copyright (c) 2006-2021, RT-Thread Development Team
 *
 * SPDX-License-Identifier: Apache-2.0
 *
 * Change Logs:
 * Date           Author       Notes
 * 2022-05-16     shelton      first version
 */

#include <rtthread.h>
#include <rtdevice.h>
#include "drv_common.h"
#include "drv_gpio.h"

/* defined the led2 pin: pd13 */
#define LED2_PIN    GET_PIN(D, 13)
/* defined the led3 pin: pd14 */
#define LED3_PIN    GET_PIN(D, 14)
/* defined the led4 pin: pd15 */
#define LED4_PIN    GET_PIN(D, 15)


static void HookDebug(struct rt_thread *from, struct rt_thread *to)
{
    //rt_kprintf("from thread:%s, to thread:%s\r\n", from->name, to->name);
}

rt_sem_t semtest;
static void TestSem1(void* pInfo)
{
    while(1) {
        rt_sem_take(semtest, RT_WAITING_FOREVER);
        //rt_kprintf("%f\r\n",0.02f);
        rt_kprintf("get sem ok\r\n");
        //Delay_ms(5000);
        rt_thread_mdelay(20);
    }
}

static void TestSem2(void* pInfo)
{
    while(1) {
        rt_sem_take(semtest, RT_WAITING_FOREVER);
        //rt_kprintf("%f\r\n",0.02f);
        rt_kprintf("get sem ok\r\n");
        //Delay_ms(5000);
        rt_thread_mdelay(20);
    }
}

static void ReleaseSemTask(void* pInfo)
{
    while(1) {
        // rt_kprintf("%f\r\n",0.02f);
        //Delay_ms(5000);
        rt_thread_mdelay(2000);
        rt_sem_release(semtest);
    }
}

int main(void)
{
    semtest = rt_sem_create("semtest", 0, 1);

    rt_scheduler_sethook(HookDebug);
    rt_thread_t testThread = rt_thread_create("test", TestSem1, NULL, 256, 0, 100);
    rt_thread_startup(testThread);

    testThread = rt_thread_create("testsem", TestSem2, NULL, 256, 0, 100);
    rt_thread_startup(testThread);

    testThread = rt_thread_create("testsem", ReleaseSemTask, NULL, 256, 0, 100);
    rt_thread_startup(testThread);
    
    while (1)
    {
        
        rt_thread_mdelay(5);
    }
}

