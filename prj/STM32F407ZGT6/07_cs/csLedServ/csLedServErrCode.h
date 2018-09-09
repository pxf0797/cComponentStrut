/**************************************************************************
* @copyright    :Copyright(C), 2018, pxf, person.
* @file         :csLedServErrCode.h
* @author       :pxf
* @version      :v1.0
* @date         :2018/09/07 22:42:51
* @brief        :组件csLedServ 内部各组成部分错误码定义头文件
* @others       :
* @history      :180907 pxf 初次建立
***************************************************************************/

#ifndef CSLEDSERVERRCODE_H_
#define CSLEDSERVERRCODE_H_

/*errClassify
************************************************************
* #define EC_EC_cie      0 // communicationInputErr   通信输入错误
* #define EC_EC_coe      1 // communicationOutputErr  通信输出错误
* #define EC_EC_se       2 // schedularErr            任务调度错误
* #define EC_EC_fe       3 // functionErr             功能错误
***********************************************************/

/*errRanking
************************************************************
* #define EC_ER_ignore   0 // ignore   可忽略
* #define EC_ER_warning  1 // warning  警告
* #define EC_ER_serious  2 // serious  严重错误
* #define EC_ER_fatal    3 // fatal    致命错误
***********************************************************/

/*errDefine
************************************************************************************************************************
*                                | csLedServPartId |   errCode  |  errClassify  |  errRanking     |
***********************************************************************************************************************/
#define csLedServ_part1_pi         0                                                              // 组件部件1
#define csLedServ_part1_err1                           0        // EC_EC_cie       EC_ER_warning  // 组件部件1错误1
/**********************************************************************************************************************/
#define csLedServ_part2_pi         1                                                              // 组件部件1
#define csLedServ_part2_err1                           0        // EC_EC_cie       EC_ER_warning  // 组件部件1错误1
/**********************************************************************************************************************/

#endif /* CSLEDSERVERRCODE_H_ */

/**************************** Copyright(C) pxf ****************************/
