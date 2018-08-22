/*
 * timer.c
 *
 * Created: 8/7/2018 7:50:48 PM
 *  Author: SirOscarin
 */ 

#include <timer.h>
#include <hal_timer.h>
#include <sensor.h>
#include <imagetesting.h>

extern struct timer_descriptor      TIMER_0;

static struct timer_task TIMER_0_task1, TIMER_0_task2;

static void TIMER_0_task1_cb(const struct timer_task *const timer_task)
{
}

static void TIMER_0_task2_cb(const struct timer_task *const timer_task)
{
	//SENSOR_vReadDevice();
	
	IMAGETESTING_vSubstractConstant();
}

void TIMER_vInit(void)
{
	TIMER_0_task1.interval = 100;
	TIMER_0_task1.cb       = TIMER_0_task1_cb;
	TIMER_0_task1.mode     = TIMER_TASK_REPEAT;
	TIMER_0_task2.interval = 200;
	TIMER_0_task2.cb       = TIMER_0_task2_cb;
	TIMER_0_task2.mode     = TIMER_TASK_REPEAT;

	timer_add_task(&TIMER_0, &TIMER_0_task1);
	timer_add_task(&TIMER_0, &TIMER_0_task2);
	timer_start(&TIMER_0);
}