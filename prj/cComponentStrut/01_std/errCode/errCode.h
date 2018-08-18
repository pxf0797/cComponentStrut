/*
 * errCode.h
 *
 *  Created on: 2018年8月18日
 *      Author: pxf
 */

#ifndef ERRCODE_H_
#define ERRCODE_H_

// 通用错误码
typedef struct
{
    void *id;                     // 由组件实例化时实现
    struct
    {
        uint32 cpnPartId    :8;   // 组件建立时为部件分配ID进行配置
        uint32 errClassify  :4;   // 通用只有4种类型
        uint32 errRanking   :4;   // 通用只有4类等级
        uint32 errCode      :16;  // 各部件ID下对应的各类错误实际进行配置
    };
} errCode, *herrCode;

// id

// cpnPartId

// errClassify
// 0  communicationInputErr  通信输入错误
// 1  communicationOutputErr 通信输出错误
// 2  schedularErr           任务调度错误
// 3  functionErr            功能错误
#define EC_EC_cie            0 // communicationInputErr
#define EC_EC_coe            1 // communicationOutputErr
#define EC_EC_se             2 // schedularErr
#define EC_EC_fe             3 // functionErr

// errRanking
// 0  ignore    可忽视
// 1  warning   警告
// 2  serious   严重错误
// 3  fatal     致命错误
#define EC_ER_ignore         0 // ignore
#define EC_ER_warning        1 // warning
#define EC_ER_serious        2 // serious
#define EC_ER_fatal          3 // fatal

// errCode


#define EC32(cpnPartId, errClassify, errRanking, errCode)       (((cpnPartId) << 24) | ((errClassify) << 20) | ((errRanking) << 16) | (errRanking))
#define EC_PID(errcode)                                         (((errcode) & 0xFF000000) >> 24)
#define EC_ECF(errcode)                                         (((errcode) & 0x00F00000) >> 20)
#define EC_ERK(errcode)                                         (((errcode) & 0x000F0000) >> 16)
#define EC_EC(errcode)                                          (((errcode) & 0x0000FFFF) >> 0)

#endif /* ERRCODE_H_ */
