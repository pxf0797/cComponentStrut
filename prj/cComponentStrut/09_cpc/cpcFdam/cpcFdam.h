/*
 * cpcFdam.h
 *
 *  Created on: 2018年8月18日
 *      Author: pxf
 */

#ifndef CPCFDAM_H_
#define CPCFDAM_H_

#include "..\..\01_std\std.h"
#include "..\..\02_bm\fifo\fifo.h"

// --------------------------------------------------------------
// 组件初始化
// --------------------------------------------------------------
// 组件输入初始化------------------------
// 0成功，-1失败
int16 vfbIcpcFdamInit(void);

// 组件初始化----------------------------
int16 cpcFdamInit(void);

// 组件输出初始化------------------------
int16 vfbOcpcFdamInit(void);

// 管理组件初始化外部声明----------------
extern int16 vfbMcpcFdamInit(void);

// --------------------------------------------------------------
// 组件调度
// --------------------------------------------------------------
// 组件进行调度--------------------------
void cpcFdamSch(void);

// --------------------------------------------------------------
// 抽象输入类通用数据类型
// --------------------------------------------------------------

// --------------------------------------------------------------
// 抽象输出类通用数据类型
// --------------------------------------------------------------

// --------------------------------------------------------------
// 抽象输出类定义
// --------------------------------------------------------------
// 抽象输出类声明------------------------
CL(vfbOcpcFdam)
{
    hvfbOcpcFdam self;
    hvfbOcpcFdam (*init)(hvfbOcpcFdam cthis);
};

// 外部接口声明--------------------------

// 抽象输出类实例------------------------
extern vfbOcpcFdam vfbOcpcFdamA;

// --------------------------------------------------------------
// 组件类定义
// --------------------------------------------------------------
// 错误处理状态机声明--------------------
#define ERR_DISPOSE_SM_LIST(_) \
    _(errDisposeSm, polling)   \
    _(errDisposeSm, dispose)
SMDC(errDisposeSm, ERR_DISPOSE_SM_LIST)
{
    sta next;
    void *cpcFdam;
};
// 错误缓存队列定义----------------------
#define ERR_FIFO_LEN     20  // 一次处理最多存储19条错误信息
extern errCode errCodeBuff[ERR_FIFO_LEN];
extern fifo errCodeFifo;

// 组件类声明----------------------------
CL(cpcFdam)
{
    hcpcFdam self;
    hcpcFdam (*init)(hcpcFdam cthis, hvfbOcpcFdam vfbOcpcFdam,
            hfifo errCodeFifo, void *listBuffer, int16 listBuffSize, int16 fifoObjSize);

    uint32 errCnt;
    // 0  ignore    可忽视
    // 1  warning   警告
    // 2  serious   严重错误
    // 3  fatal     致命错误
    uint32 errIgnoreCnt;
    uint32 errWarningCnt;
    uint32 errSeriousCnt;
    uint32 errFatalCnt;
    // 0  communicationInputErr  通信输入错误
    // 1  communicationOutputErr 通信输出错误
    // 2  schedularErr           任务调度错误
    // 3  functionErr            功能错误
    uint32 errCieCnt;
    uint32 errCoeCnt;
    uint32 errSeCnt;
    uint32 errFeCnt;

    errDisposeSmRec errDisposeSmRec;
    staAct errDisposeSm[errDisposeSm_sta_default + 1];

    void (*saveErrCode)(hcpcFdam t, herrCode code);
//    void (*getErrCode)(hcpcFdam t, herrCode code);
    void (*run)(hcpcFdam t);

    INJ(vfbOcpcFdam, vfbOcpcFdam);
    EXT(fifo);
};

// 异步调度功能函数----------------------


// 组件类实例----------------------------
extern cpcFdam cpcFdamA;

// --------------------------------------------------------------
// 抽象输入类定义
// --------------------------------------------------------------
// 抽象输入类声明------------------------
CL(vfbIcpcFdam)
{
    hvfbIcpcFdam self;
    hvfbIcpcFdam (*init)(hvfbIcpcFdam cthis, hcpcFdam cpcFdam);

    void (*saveErrCode)(hvfbIcpcFdam t, herrCode code);

    INJ(cpcFdam, cpcFdam);
};

// 抽象输入类实例------------------------
extern vfbIcpcFdam vfbIcpcFdamA;

#endif /* CPCFDAM_H_ */
