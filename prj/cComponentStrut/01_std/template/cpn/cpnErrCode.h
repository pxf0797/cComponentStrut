/*
 * cpnErrCode.h
 *
 *  Created on: 2018年8月18日
 *      Author: pxf
 */

#ifndef CPNERRCODE_H_
#define CPNERRCODE_H_

// errClassify
// 0  communicationInputErr  通信输入错误
// 1  communicationOutputErr 通信输出错误
// 2  schedularErr           任务调度错误
// 3  functionErr            功能错误
//#define EC_EC_cie            0 // communicationInputErr
//#define EC_EC_coe            1 // communicationOutputErr
//#define EC_EC_se             2 // schedularErr
//#define EC_EC_fe             3 // functionErr

// errRanking
// 0  ignore    可忽视
// 1  warning   警告
// 2  serious   严重错误
// 3  fatal     致命错误
//#define EC_ER_ignore         0 // ignore
//#define EC_ER_warning        1 // warning
//#define EC_ER_serious        2 // serious
//#define EC_ER_fatal          3 // fatal

// --------------------------------------------------------------
// 组件内部错误码
// --------------------------------------------------------------
//                                        cpnPartId      errCode       errClassify        errRanking
// casSch_addTask
//#define casSch_addTask_pi                 0                                                                 // 添加任务
//#define casSch_addTask_id_outOfRange                     0          // EC_EC_se           EC_ER_warning     // id超出范围
//#define casSch_addTask_task_exist                        1          // EC_EC_se           EC_ER_warning     // 任务已存在

// casSch_delTask
//#define casSch_delTask_pi                 1                                                                 // 删除任务
//#define casSch_delTask_id_outOfRange                     0          // EC_EC_se           EC_ER_warning     // 删除任务失败
//#define casSch_delTask_task_null                         1          // EC_EC_se           EC_ER_warning     // 任务不存在
//#define casSch_delTask_task_false                        2          // EC_EC_se           EC_ER_warning     // 非目标任务

#endif /* CPNERRCODE_H_ */
