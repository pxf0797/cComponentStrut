/**************************************************************************
* @copyright    :Copyright(C), 2018, pxf, person.
* @file         :casSchCfg.h
* @author       :pxf
* @version      :v1.0
* @date         :2018/08/31 20:52:28
* @brief        :组件casSch 配置头文件
* @others       :
* @history      :180831 pxf 初次建立
***************************************************************************/

#ifndef CASSCHCFG_H_
#define CASSCHCFG_H_

/*组件调度参数配置
***********************************************************/
#define SCH_TASK_GROUP_NUM_CFG                     2           // 调度任务组设置，任务组越多耗时越长，按实际需求来进行配置
#define CASSCH_TIMER_PRD_CFG                       100000.0L   // 异步定时调度函数调度周期，单位ns
#define CASSCH_TIME_MEASURE_PRECISION_CFG          100.0L      // 时间测量函数精度，单位ns

/*组件功能开启配置
***********************************************************/
#define CASSCH_TASK_MEASURE_ENABLE                 1           // 是否对任务开启时间测量及计算cpu使用率，0关闭，1开启

#endif

/**************************** Copyright(C) pxf ****************************/
