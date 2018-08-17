/*
 * casSch.h
 *
 *  Created on: 2018年8月17日
 *      Author: pxf
 */

#ifndef CASSCH_H_
#define CASSCH_H_

#include "..\..\01_std\std.h"
#include "..\..\04_abi\abi.h"

// 调度器管理状态机
#define SCH_SM_STA_LIST(_) \
    _(schSm, update) \
    _(schSm, execute)

SMDC(schSm, SCH_SM_STA_LIST)
{
    sta next;
};


// 通用错误码
typedef struct
{
    void *id;
    struct
    {
        uint32 cpnPartId    :8;
        uint32 errClassify  :4;
        uint32 errRanking   :4;
        uint32 errCode      :16;
    };
} errCode, *herrCode;

// 抽象输出类定义
CL(vfbOcasSch)
{
    hvfbOcasSch self;
    hvfbOcasSch (*init)(hvfbOcasSch cthis,
            void (*tickOut)(hvfbOcasSch t),
            void (*err)(hvfbOcasSch t, herrCode code));

    void (*tickOut)(hvfbOcasSch t);
    void (*err)(hvfbOcasSch t, herrCode code);
};


// 组件类定义
// 任务组
#define SCH_TASK_GROUP_NUM  3  // 调度任务组

typedef void(*schTask)(void);

typedef struct
{
    int16 taskGroupNum;
    uint16 actTick[SCH_TASK_GROUP_NUM];           // 激活节拍
    uint16 prdTick[SCH_TASK_GROUP_NUM];           // 周期调度节拍
    uint32 actMask[SCH_TASK_GROUP_NUM];           // 激活请求任务掩码
    uint32 taskMask[SCH_TASK_GROUP_NUM];          // 已分配任务掩码
    schTask taskGroup[SCH_TASK_GROUP_NUM][32];    // 任务组
} tasks;


CL(casSch)
{
    hcasSch self;
    hcasSch (*init)(hcasSch cthis, hmeasure time);

    uint16 tick;
    tasks task;
    schSmRec schSmRec;

    // 自身功能函数
    void (*timer)(hcasSch t);
    void (*run)(hcasSch t);

    // 输出函数
    void (*tickOut)(hcasSch t);
    void (*err)(hcasSch t, herrCode code);

    // 输入函数
    void (*addTask)(hcasSch t, int16 id, void(*schTask)(void));
    void (*delTask)(hcasSch t, int16 id, void(*schTask)(void));

    INJ(measure, time);
    INJ(vfbOcasSch, vfbOcasSch);
};

// 抽象输入类定义
CL(vfbIcasSch)
{
    hvfbIcasSch self;
    hvfbIcasSch (*init)(hvfbIcasSch cthis);

    void (*addTask)(hvfbIcasSch t, int16 id, void(*schTask)(void));
    void (*delTask)(hvfbIcasSch t, int16 id, void(*schTask)(void));

    INJ(casSch, casSch);
};

// 异步调度功能函数
void casSch_timer_bsp(void);
void casSch_mainLoop_bsp(void);

// 抽象类功能接口



#endif /* CASSCH_H_ */
