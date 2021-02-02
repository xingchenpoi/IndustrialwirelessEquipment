/*******************************************************************************
**              广州中科院沈阳自动化研究所分所 Copyright (c)
**                     物联网技术与应用研发中心
**                        IM(2019-2022)
** 作    者：viggo
** 日    期：
** 文件名称：APP_Scheduler.c
** 摘    要：任务调度




*******************************************************************************/
/*--------------------------------- 头文件 -----------------------------------*/
#include "APP_Scheduler.h"        // 头文件                                                          

/*--------------------------------- 私有变量 -----------------------------------*/
extern void TASK_1_MAIN_FUNC();

#if cSETUP_NUMBER_OF_TASKS > 1
extern void TASK_2_MAIN_FUNC();
#endif 

#if cSETUP_NUMBER_OF_TASKS > 2
extern void TASK_3_MAIN_FUNC();
#endif

#if cSETUP_NUMBER_OF_TASKS > 3
extern void TASK_4_MAIN_FUNC();
#endif

#if cSETUP_NUMBER_OF_TASKS > 4
extern void TASK_5_MAIN_FUNC();
#endif

#if cSETUP_NUMBER_OF_TASKS > 5
extern void TASK_6_MAIN_FUNC();
#endif

#if cSETUP_NUMBER_OF_TASKS > 6
extern void TASK_7_MAIN_FUNC();
#endif

#if cSETUP_NUMBER_OF_TASKS > 7
extern void TASK_8_MAIN_FUNC();
#endif

#if cSETUP_NUMBER_OF_TASKS > 8
extern void TASK_9_MAIN_FUNC();
#endif

#if cSETUP_NUMBER_OF_TASKS > 9
extern void TASK_10_MAIN_FUNC();
#endif

#if cSETUP_NUMBER_OF_TASKS > 10
extern void TASK_11_MAIN_FUNC();
#endif

#if cSETUP_NUMBER_OF_TASKS > 11
extern void TASK_12_MAIN_FUNC();
#endif

#if cSETUP_NUMBER_OF_TASKS > 12
extern void TASK_13_MAIN_FUNC();
#endif

#if cSETUP_NUMBER_OF_TASKS > 13
extern void TASK_14_MAIN_FUNC();
#endif

#if cSETUP_NUMBER_OF_TASKS > 14
extern void TASK_15_MAIN_FUNC();
#endif

#if cSETUP_NUMBER_OF_TASKS > 15
extern void TASK_16_MAIN_FUNC();
#endif

#if cSETUP_NUMBER_OF_TASKS > 16
extern void TASK_17_MAIN_FUNC();
#endif

#if cSETUP_NUMBER_OF_TASKS > 17
extern void TASK_18_MAIN_FUNC();
#endif

#if cSETUP_NUMBER_OF_TASKS > 18
extern void TASK_19_MAIN_FUNC();
#endif

#if cSETUP_NUMBER_OF_TASKS > 19
extern void TASK_20_MAIN_FUNC();
#endif

#if cSETUP_NUMBER_OF_TASKS > 20
extern void TASK_21_MAIN_FUNC();
#endif

#if cSETUP_NUMBER_OF_TASKS > 21
extern void TASK_22_MAIN_FUNC();
#endif

#if cSETUP_NUMBER_OF_TASKS > 22
extern void TASK_23_MAIN_FUNC();
#endif

#if cSETUP_NUMBER_OF_TASKS > 23
extern void TASK_24_MAIN_FUNC();
#endif

#if cSETUP_NUMBER_OF_TASKS > 24
extern void TASK_25_MAIN_FUNC();
#endif

#if cSETUP_NUMBER_OF_TASKS > 25
extern void TASK_26_MAIN_FUNC();
#endif

#if cSETUP_NUMBER_OF_TASKS > 26
extern void TASK_27_MAIN_FUNC();
#endif

#if cSETUP_NUMBER_OF_TASKS > 27
extern void TASK_28_MAIN_FUNC();
#endif

#if cSETUP_NUMBER_OF_TASKS > 28
extern void TASK_29_MAIN_FUNC();
#endif

#if cSETUP_NUMBER_OF_TASKS > 29
extern void TASK_30_MAIN_FUNC();
#endif

#if cSETUP_NUMBER_OF_TASKS > 30
extern void TASK_31_MAIN_FUNC();
#endif

#if cSETUP_NUMBER_OF_TASKS > 31
extern void TASK_32_MAIN_FUNC();
#endif

/*-------------------------------- 全局变量 ----------------------------------*/
//点控表声明
const tab_ptr_function Setup_Tasks_Table[] =
{
   &TASK_1_MAIN_FUNC

#if cSETUP_NUMBER_OF_TASKS > 1
  ,&TASK_2_MAIN_FUNC
#else
  ,NULL
#endif 

#if cSETUP_NUMBER_OF_TASKS > 2
  ,&TASK_3_MAIN_FUNC
#else
  ,NULL
#endif 

#if cSETUP_NUMBER_OF_TASKS > 3
  ,&TASK_4_MAIN_FUNC
#else
  ,NULL
#endif 

#if cSETUP_NUMBER_OF_TASKS > 4
  ,&TASK_5_MAIN_FUNC
#else
  ,NULL
#endif 

#if cSETUP_NUMBER_OF_TASKS > 5
  ,&TASK_6_MAIN_FUNC
#else
  ,NULL
#endif 

#if cSETUP_NUMBER_OF_TASKS > 6
  ,&TASK_7_MAIN_FUNC
#else
  ,NULL
#endif 

#if cSETUP_NUMBER_OF_TASKS > 7
   ,&TASK_8_MAIN_FUNC
#else
  ,NULL
#endif 

#if cSETUP_NUMBER_OF_TASKS > 8
   ,&TASK_9_MAIN_FUNC
#else
  ,NULL
#endif 

#if cSETUP_NUMBER_OF_TASKS > 9
   ,&TASK_10_MAIN_FUNC
#else
  ,NULL
#endif 

#if cSETUP_NUMBER_OF_TASKS > 10
   ,&TASK_11_MAIN_FUNC
#else
  ,NULL
#endif 

#if cSETUP_NUMBER_OF_TASKS > 11
   ,&TASK_12_MAIN_FUNC
#else
  ,NULL
#endif 

#if cSETUP_NUMBER_OF_TASKS > 12
   ,&TASK_13_MAIN_FUNC
#else
  ,NULL
#endif 

#if cSETUP_NUMBER_OF_TASKS > 13
   ,&TASK_14_MAIN_FUNC
#else
  ,NULL
#endif 

#if cSETUP_NUMBER_OF_TASKS > 14
   ,&TASK_15_MAIN_FUNC
#else
  ,NULL
#endif 

#if cSETUP_NUMBER_OF_TASKS > 15
   ,&TASK_16_MAIN_FUNC
#else
  ,NULL
#endif 

#if cSETUP_NUMBER_OF_TASKS > 16 
   ,&TASK_17_MAIN_FUNC
#else
  ,NULL
#endif 

#if cSETUP_NUMBER_OF_TASKS > 17
   ,&TASK_18_MAIN_FUNC
#else
  ,NULL
#endif 

#if cSETUP_NUMBER_OF_TASKS > 18
   ,&TASK_19_MAIN_FUNC
#else
  ,NULL
#endif 

#if cSETUP_NUMBER_OF_TASKS > 19
   ,&TASK_20_MAIN_FUNC
#else
  ,NULL
#endif 

#if cSETUP_NUMBER_OF_TASKS > 20
   ,&TASK_21_MAIN_FUNC
#else
  ,NULL
#endif 

#if cSETUP_NUMBER_OF_TASKS > 21
   ,&TASK_22_MAIN_FUNC
#else
  ,NULL
#endif 

#if cSETUP_NUMBER_OF_TASKS > 22
   ,&TASK_23_MAIN_FUNC
#else
  ,NULL
#endif 

#if cSETUP_NUMBER_OF_TASKS > 23
   ,&TASK_24_MAIN_FUNC
#else
  ,NULL
#endif 

#if cSETUP_NUMBER_OF_TASKS > 24
   ,&TASK_25_MAIN_FUNC
#else
  ,NULL
#endif 

#if cSETUP_NUMBER_OF_TASKS > 25
   ,&TASK_26_MAIN_FUNC
#else
  ,NULL
#endif 

#if cSETUP_NUMBER_OF_TASKS > 26
   ,&TASK_27_MAIN_FUNC
#else
  ,NULL
#endif 

#if cSETUP_NUMBER_OF_TASKS > 27
   ,&TASK_28_MAIN_FUNC
#else
  ,NULL
#endif 

#if cSETUP_NUMBER_OF_TASKS > 28
   ,&TASK_29_MAIN_FUNC
#else
  ,NULL
#endif 

#if cSETUP_NUMBER_OF_TASKS > 29
   ,&TASK_30_MAIN_FUNC
#else
  ,NULL
#endif 

#if cSETUP_NUMBER_OF_TASKS > 30
   ,&TASK_31_MAIN_FUNC
#else
  ,NULL
#endif 

#if cSETUP_NUMBER_OF_TASKS > 31
   ,&TASK_32_MAIN_FUNC
#else
  ,NULL
#endif 
};

//调度程序排序表声明
const uint32_t Setup_Sched_table[] =
{
	SCHED1_STEP_1_ACTIVABLE_TASKS

#if cSETUP_SCHED1_STEP_NUMBER > 1
	,SCHED1_STEP_2_ACTIVABLE_TASKS
#endif

#if cSETUP_SCHED1_STEP_NUMBER > 2
	,SCHED1_STEP_3_ACTIVABLE_TASKS
#endif

#if cSETUP_SCHED1_STEP_NUMBER > 3
	,SCHED1_STEP_4_ACTIVABLE_TASKS
#endif

#if cSETUP_SCHED1_STEP_NUMBER > 4
	,SCHED1_STEP_5_ACTIVABLE_TASKS
#endif

#if cSETUP_SCHED1_STEP_NUMBER > 5
	,SCHED1_STEP_6_ACTIVABLE_TASKS
#endif

#if cSETUP_SCHED1_STEP_NUMBER > 6
	,SCHED1_STEP_7_ACTIVABLE_TASKS
#endif

#if cSETUP_SCHED1_STEP_NUMBER > 7
	,SCHED1_STEP_8_ACTIVABLE_TASKS
#endif

#if cSETUP_SCHED1_STEP_NUMBER > 8
	,SCHED1_STEP_9_ACTIVABLE_TASKS
#endif

#if cSETUP_SCHED1_STEP_NUMBER > 9
	,SCHED1_STEP_10_ACTIVABLE_TASKS
#endif

#if cSETUP_SCHED1_STEP_NUMBER > 10
	,SCHED1_STEP_11_ACTIVABLE_TASKS
#endif

#if cSETUP_SCHED1_STEP_NUMBER > 11
	,SCHED1_STEP_12_ACTIVABLE_TASKS
#endif

#if cSETUP_SCHED1_STEP_NUMBER > 12
	,SCHED1_STEP_13_ACTIVABLE_TASKS
#endif

#if cSETUP_SCHED1_STEP_NUMBER > 13
	,SCHED1_STEP_14_ACTIVABLE_TASKS
#endif

#if cSETUP_SCHED1_STEP_NUMBER > 14
	,SCHED1_STEP_15_ACTIVABLE_TASKS
#endif

#if cSETUP_SCHED1_STEP_NUMBER > 15
	,SCHED1_STEP_16_ACTIVABLE_TASKS
#endif

#if cSETUP_SCHED1_STEP_NUMBER > 16
	,SCHED1_STEP_17_ACTIVABLE_TASKS
#endif

#if cSETUP_SCHED1_STEP_NUMBER > 17
	,SCHED1_STEP_18_ACTIVABLE_TASKS
#endif

#if cSETUP_SCHED1_STEP_NUMBER > 18
	,SCHED1_STEP_19_ACTIVABLE_TASKS
#endif

#if cSETUP_SCHED1_STEP_NUMBER > 19
	,SCHED1_STEP_20_ACTIVABLE_TASKS
#endif

#if cSETUP_SCHED1_STEP_NUMBER > 20
	,SCHED1_STEP_21_ACTIVABLE_TASKS
#endif

#if cSETUP_SCHED1_STEP_NUMBER > 21
	,SCHED1_STEP_22_ACTIVABLE_TASKS
#endif

#if cSETUP_SCHED1_STEP_NUMBER > 22
	,SCHED1_STEP_23_ACTIVABLE_TASKS
#endif

#if cSETUP_SCHED1_STEP_NUMBER > 23
	,SCHED1_STEP_24_ACTIVABLE_TASKS
#endif

#if cSETUP_SCHED1_STEP_NUMBER > 24
	,SCHED1_STEP_25_ACTIVABLE_TASKS
#endif

#if cSETUP_SCHED1_STEP_NUMBER > 25
	,SCHED1_STEP_26_ACTIVABLE_TASKS
#endif

#if cSETUP_SCHED1_STEP_NUMBER > 26
	,SCHED1_STEP_27_ACTIVABLE_TASKS
#endif

#if cSETUP_SCHED1_STEP_NUMBER > 27
	,SCHED1_STEP_28_ACTIVABLE_TASKS
#endif

#if cSETUP_SCHED1_STEP_NUMBER > 28
	,SCHED1_STEP_29_ACTIVABLE_TASKS
#endif

#if cSETUP_SCHED1_STEP_NUMBER > 29
	,SCHED1_STEP_30_ACTIVABLE_TASKS
#endif

#if cSETUP_SCHED1_STEP_NUMBER > 30
	,SCHED1_STEP_31_ACTIVABLE_TASKS
#endif

#if cSETUP_SCHED1_STEP_NUMBER > 31
	,SCHED1_STEP_32_ACTIVABLE_TASKS
#endif
};

//启动任务数量
const uint8_t Setup_Number_of_tasks = cSETUP_NUMBER_OF_TASKS;
//调度步骤
const uint8_t Setup_sched_step_number = cSETUP_SCHED1_STEP_NUMBER;

//设置激活工作计数
uint8_t Setup_CountActivateJob = 0;
//设置激活任务步骤
uint8_t Setup_CountActivateTaskStep = 0;
//设置激活工作列表的任务
uint32_t Setup_ListOfActivateJob;


/*******************************************************************************
** 函数原型：void SCHED_Setup_entry(void)
** 函数功能：调度设置入口
** 输入参数：无
** 输出参数：无
** 备    注：

*******************************************************************************/
void SCHED_Setup_entry(void)
{
	//获取当前激活的任务
	Setup_ListOfActivateJob = Setup_Sched_table[Setup_CountActivateTaskStep];
	//设置激活工作计数清零
	Setup_CountActivateJob = 0;

	//循环执行工作列表中的任务，直到处理完成
	while (Setup_CountActivateJob <= Setup_Number_of_tasks)
	{
		//判断任务是否激活
		if (((Setup_ListOfActivateJob >> Setup_CountActivateJob) & 0x0001) == 1)
		{
			/* 执行任务 */
			Setup_Tasks_Table[Setup_CountActivateJob].task_main_func_ptr();
		}

		Setup_CountActivateJob++;
	}

	//判断调度步骤是否执行完成
	if (Setup_CountActivateTaskStep < (Setup_sched_step_number - 1))
	{
		Setup_CountActivateTaskStep++;
	}
	else
	{
		Setup_CountActivateTaskStep = 0;
	}
}

/*******************************************************************************
*   版本号        修改日期        修改者        修改内容
*
*******************************************************************************/

/*--------------------------------文件结尾------------------------------------*/
