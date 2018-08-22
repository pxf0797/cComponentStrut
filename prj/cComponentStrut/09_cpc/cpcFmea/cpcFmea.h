/*
 * cpcFmea.h
 *
 *  Created on: 2018年8月22日
 *      Author: pxf
 */

#ifndef CPCFMEA_H_
#define CPCFMEA_H_

#include "..\..\01_std\std.h"
#include "..\..\02_bm\fifo\fifo.h"
#include "..\..\06_cas\casSch\casSch.h"
#include "cpcFmeaCfg.h"

// --------------------------------------------------------------
// 组件初始化
// --------------------------------------------------------------
// 组件输入初始化------------------------
// 0成功，-1失败
int16 vfbIcpcFmeaInit(void);

// 组件初始化----------------------------
int16 cpcFmeaInit(void);

// 组件输出初始化------------------------
int16 vfbOcpcFmeaInit(void);

// 管理组件初始化外部声明----------------
extern int16 vfbMcpcFmeaInit(void);

// --------------------------------------------------------------
// 组件调度
// --------------------------------------------------------------
// 组件进行调度--------------------------
void cpcFmeaSch(void);

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
CL(vfbOcpcFmea)
{
    hvfbOcpcFmea self;
    hvfbOcpcFmea (*init)(hvfbOcpcFmea cthis);

    schParam schParam;
};

// 外部接口声明--------------------------

// 抽象输出类实例------------------------
extern vfbOcpcFmea vfbOcpcFmeaA;

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
    void *cpcFmea;
};
// 错误缓存队列定义----------------------
#define ERR_FIFO_LEN     ERR_FIFO_LEN_CFG  // 一次处理最多存储错误信息
extern errCode errCodeBuff[ERR_FIFO_LEN];
extern fifo errCodeFifo;

// 组件类声明----------------------------
CL(cpcFmea)
{
    hcpcFmea self;
    hcpcFmea (*init)(hcpcFmea cthis, hvfbOcpcFmea vfbOcpcFmea,
            hfifo errCodeFifo, void *listBuffer, int16 listBuffSize, int16 fifoObjSize,
            hstaAct errDisposeSm);

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
    hstaAct errDisposeSm;

//    schParam schParam;

    void (*saveErrCode)(hcpcFmea t, herrCode code);
    void (*run)(hcpcFmea t);

    INJ(vfbOcpcFmea, vfbOcpcFmea);
    EXT(fifo);
};

// 异步调度功能函数----------------------


// 组件类实例----------------------------
extern cpcFmea cpcFmeaA;

// --------------------------------------------------------------
// 抽象输入类定义
// --------------------------------------------------------------
// 抽象输入类声明------------------------
CL(vfbIcpcFmea)
{
    hvfbIcpcFmea self;
    hvfbIcpcFmea (*init)(hvfbIcpcFmea cthis, hcpcFmea cpcFmea);

//    schParam schParam;

    void (*saveErrCode)(hvfbIcpcFmea t, herrCode code);

    INJ(cpcFmea, cpcFmea);
};

// 抽象输入类实例------------------------
extern vfbIcpcFmea vfbIcpcFmeaA;

#endif /* CPCFMEA_H_ */
