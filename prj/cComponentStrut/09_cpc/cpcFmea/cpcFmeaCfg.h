/**************************************************************************
* @copyright    :Copyright(C), 2018, pxf, person.
* @file         :cpcFmeaCfg.h
* @author       :pxf
* @version      :v1.0
* @date         :2018/09/07 21:33:44
* @brief        :组件cpcFmea 配置头文件
* @others       :
* @history      :180907 pxf 初次建立
***************************************************************************/

#ifndef CPCFMEACFG_H_
#define CPCFMEACFG_H_

/*组件调度参数配置
***********************************************************/
#define CPCFMEA_PRD_TICK_CFG        10000000.0L    // 任务调度周期配置(ns),10ms
#define CPCFMEA_START_TICK_CFG      3000000.0L     // 任务调度启动配置(ns),3ms

/*错误码缓存队列长度配置
***********************************************************/
#define CPCFMEA_ERRCODE_FIFO_LEN_CFG 20            // 错误码缓存队列长度配置


#endif /* CPCFMEACFG_H_ */

/**************************** Copyright(C) pxf ****************************/
