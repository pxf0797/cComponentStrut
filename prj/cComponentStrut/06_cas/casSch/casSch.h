/**************************************************************************
* @copyright    :Copyright(C), 2018, pxf, person.
* @file         :casSch.h
* @author       :pxf
* @version      :v1.0
* @date         :2018/08/31 20:52:28
* @brief        :组件casSch 输入类、组件类、输出类数据类型声明头文件
* @others       :
* @history      :180831 pxf 初次建立
***************************************************************************/

#ifndef CASSCH_H_
#define CASSCH_H_

#include "..\..\01_std\std.h"
//#include "..\..\06_cas\casSch\casSch.h"
#include "..\..\04_abi\abi.h"
#include "casSchCfg.h"
#include "casSchErrCode.h"

/***********************************************************
* 组件初始化
***********************************************************/
/*组件输入初始化
* 输入: 无
* 输出: int16 0-成功,-1-失败
***********************************************/
int16 vfbIcasSchInit(void);

/*组件初始化
* 输入: 无
* 输出: int16 0-成功,-1-失败
***********************************************/
int16 casSchInit(void);

/*组件输出初始化
* 输入: 无
* 输出: int16 0-成功,-1-失败
***********************************************/
int16 vfbOcasSchInit(void);

/*管理组件初始化外部声明
* 输入: 无
* 输出: int16 0-成功,-1-失败
***********************************************/
extern int16 vfbMcasSchInit(void);


/***********************************************************
* 组件调度
***********************************************************/
/*组件进行调度
* 输入: 无
* 输出: 无
***********************************************/
//void casSchSch(void);


/***********************************************************
* 组件输入类通用数据类型
***********************************************************/


/***********************************************************
* 组件输出类通用数据类型
***********************************************************/


/***********************************************************
* 组件输出类定义
***********************************************************/
/*组件输出类声明
***********************************************/
CL(vfbOcasSch){
    hvfbOcasSch self;
    hvfbOcasSch (*init)(hvfbOcasSch cthis,
            void (*tickOut)(hvfbOcasSch t),
            void (*err)(hvfbOcasSch t, herrCode code));

    // 组件调度参数
    //schParam schParam;

    // 组件输出类功能函数
    void (*tickOut)(hvfbOcasSch t);
    void (*err)(hvfbOcasSch t, herrCode code);
};

/*组件输出类外部接口声明
* 命名方式: 存放类+实际类+实际类功能
***********************************************/
extern void vfbMcasSch_vfbOcasSch_tickOut(hvfbOcasSch t);
extern void vfbMcasSch_vfbOcasSch_err(hvfbOcasSch t, herrCode code);

/*组件输出类实例
***********************************************/
extern vfbOcasSch vfbOcasSchA;


/***********************************************************
* 组件类定义
***********************************************************/
/*任务组
***********************************************/
#define SCH_TASK_GROUP_NUM  SCH_TASK_GROUP_NUM_CFG   // 调度任务组设置
typedef void(*schTask)(void);                        // 通用调度任务类型

/*任务管理组定义
***********************************************/
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

/*组件状态机状态
* 有两个状态init/default，状态list不显示，默认给出
* 状态list需根据实际应用进行重写，list修改后相应状态函数得对应修改
***********************************************/
#define SM_CASSCH_STA_LIST(_) \
    _(smcasSch, update)\
    _(smcasSch, execute)

/*组件状态机定义
***********************************************/
SMDC(smcasSch, SM_CASSCH_STA_LIST)
{
    sta next;
    tasks task;

    // 注入组件类
    void *casSch;
};

/*组件调度调度参数（其他组件必含成员）
***********************************************/
typedef struct
{
    int16 id;                // 组件调度id，由组件初始化时分配
    void(*schTask)(void);    // 调度组件
    uint16 startTick;        // 调度周期起始节拍
    uint16 prdTick;          // 周期调度节拍
} schParam;

/*组件类声明
***********************************************/
CL(casSch){
    hcasSch self;
    hcasSch (*init)(hcasSch cthis, hstaAct smcasSch, hvfbOcasSch vfbOcasSch, hmeasure time);

    // 组件运行状态机
    smcasSchRec smcasSchRec;
    hstaAct smcasSch;

    // 组件运行相关参数
    uint32 usage;        // cpu使用率，如112表示11.2%
    uint32 taskTime;     // 当前任务执行时间，与时间测量结果一致

    // 组件运行功能函数
    void (*run)(hcasSch t);
    void (*tick)(hcasSch t);

    // 组件输入功能函数
    void (*addTask)(hcasSch t, int16 id, void(*schTask)(void), uint16 prdTick, uint16 startTick);
    void (*delTask)(hcasSch t, int16 id, void(*schTask)(void));

    // 组件输出功能函数
    void (*tickOut)(hcasSch t);
    void (*err)(hcasSch t, herrCode code);

    // 注入组件输出类及其他功能类
    INJ(vfbOcasSch, vfbOcasSch);
    INJ(measure, time);
};

/*异步调度功能函数
* 命名方式: 存放类+实际类+实际类功能
* 只有cas类型组件才有此函数
***********************************************/
void casSch_abi_timer(void);
void casSch_abi_mainLoop(void);

/*组件类实例
***********************************************/
extern casSch casSchA;


/***********************************************************
* 组件输入类定义
***********************************************************/
/*组件输入类声明
***********************************************/
CL(vfbIcasSch){
    hvfbIcasSch self;
    hvfbIcasSch (*init)(hvfbIcasSch cthis, hcasSch casSch);

    // 组件输入类功能函数
    void (*addTask)(hvfbIcasSch t, int16 id, void(*schTask)(void), uint16 prdTick, uint16 startTick);
    void (*delTask)(hvfbIcasSch t, int16 id, void(*schTask)(void));

    // 注入组件类
    INJ(casSch, casSch);
};

/*组件输入类实例
***********************************************/
extern vfbIcasSch vfbIcasSchA;


#endif

/**************************** Copyright(C) pxf ****************************/
