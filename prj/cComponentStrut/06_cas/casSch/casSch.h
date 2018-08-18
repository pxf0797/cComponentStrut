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
#include "casSchErrCode.h"

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
CL(vfbOcasSch)
{
    hvfbOcasSch self;
    hvfbOcasSch (*init)(hvfbOcasSch cthis,
            void (*tickOut)(hvfbOcasSch t),
            void (*err)(hvfbOcasSch t, herrCode code));

    void (*tickOut)(hvfbOcasSch t);
    void (*err)(hvfbOcasSch t, herrCode code);
};

// 外部接口声明--------------------------
void vfbMcasSch_vfbOcasSch_tickOut(hvfbOcasSch t);                 // 接口结构：存放类+功能类+功能类函数
void vfbMcasSch_vfbOcasSch_err(hvfbOcasSch t, herrCode code);

// 抽象输出类实例------------------------
extern vfbOcasSch vfbOcasSchA;


// --------------------------------------------------------------
// 组件类定义
// --------------------------------------------------------------
// 任务组--------------------------------
#define SCH_TASK_GROUP_NUM  3  // 调度任务组设置
typedef void(*schTask)(void);  // 通用调度任务类型
// 任务管理组定义
typedef struct
{
    int16 taskGroupNum;
    uint16 tick;
    uint16 startTick[SCH_TASK_GROUP_NUM][32];     // 调度周期起始节拍
    uint16 prdTick[SCH_TASK_GROUP_NUM][32];       // 周期调度节拍
    uint32 actMask[SCH_TASK_GROUP_NUM];           // 激活请求任务掩码
    uint32 taskMask[SCH_TASK_GROUP_NUM];          // 已分配任务掩码
    schTask taskGroup[SCH_TASK_GROUP_NUM][32];    // 任务组
} tasks;

// 调度器管理状态机-----------------------
#define SCH_SM_STA_LIST(_) \
    _(schSm, update) \
    _(schSm, execute)

// 调度状态机定义
SMDC(schSm, SCH_SM_STA_LIST)
{
    sta next;
    tasks task;

    // 注入任务调度类组件本身
    void *casSch;
};

// 调度任务组件类声明----------------------
CL(casSch)
{
    hcasSch self;
    hcasSch (*init)(hcasSch cthis, hmeasure time, hvfbOcasSch vfbOcasSch);

    schSmRec schSmRec;
    staAct schSm[schSm_sta_default + 1];

    // 自身功能函数
    void (*timer)(hcasSch t);
    void (*run)(hcasSch t);

    // 输出函数
    void (*tickOut)(hcasSch t);
    void (*err)(hcasSch t, herrCode code);

    // 输入函数
    void (*addTask)(hcasSch t, int16 id, void(*schTask)(void), uint16 prdTick, uint16 startTick);
    void (*delTask)(hcasSch t, int16 id, void(*schTask)(void));

    INJ(measure, time);
    INJ(vfbOcasSch, vfbOcasSch);
};

// 异步调度功能函数---------------------------
void abi_casSch_timer(void);
void abi_casSch_mainLoop(void);

// 组件类实例---------------------------------
extern casSch casSchA;

// --------------------------------------------------------------
// 抽象输入类定义
// --------------------------------------------------------------
// 抽象输入类声明------------------------------
CL(vfbIcasSch)
{
    hvfbIcasSch self;
    hvfbIcasSch (*init)(hvfbIcasSch cthis, hcasSch casSch);

    void (*addTask)(hvfbIcasSch t, int16 id, void(*schTask)(void), uint16 prdTick, uint16 startTick);
    void (*delTask)(hvfbIcasSch t, int16 id, void(*schTask)(void));

    INJ(casSch, casSch);
};

// 抽象输入类实例------------------------------
extern vfbIcasSch vfbIcasSchA;

#endif /* CASSCH_H_ */
