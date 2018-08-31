/**************************************************************************
* @copyright    :Copyright(C), 2018, pxf, person.
* @file         :csLedServ.h
* @author       :pxf
* @version      :v1.0
* @date         :2018/08/31 23:21:10
* @brief        :组件csLedServ 输入类、组件类、输出类数据类型声明头文件
* @others       :
* @history      :180831 pxf 初次建立
***************************************************************************/

#ifndef CSLEDSERV_H_
#define CSLEDSERV_H_

#include "..\..\01_std\std.h"
#include "..\..\06_cas\casSch\casSch.h"
#include "csLedServCfg.h"
#include "csLedServErrCode.h"

/***********************************************************
* 组件初始化
***********************************************************/
/*组件输入初始化
* 输入: 无
* 输出: int16 0-成功,-1-失败
***********************************************/
int16 vfbIcsLedServInit(void);

/*组件初始化
* 输入: 无
* 输出: int16 0-成功,-1-失败
***********************************************/
int16 csLedServInit(void);

/*组件输出初始化
* 输入: 无
* 输出: int16 0-成功,-1-失败
***********************************************/
int16 vfbOcsLedServInit(void);

/*管理组件初始化外部声明
* 输入: 无
* 输出: int16 0-成功,-1-失败
***********************************************/
extern int16 vfbMcsLedServInit(void);


/***********************************************************
* 组件调度
***********************************************************/
/*组件进行调度
* 输入: 无
* 输出: 无
***********************************************/
void csLedServSch(void);


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
CL(vfbOcsLedServ){
    hvfbOcsLedServ self;
    hvfbOcsLedServ (*init)(hvfbOcsLedServ cthis);

    // 组件调度参数
    schParam schParam;

    // 组件输出类功能函数
    //void (*output)(hvfbOcsLedServ t);
    //TODO
};

/*组件输出类外部接口声明
* 命名方式: 存放类+实际类+实际类功能
***********************************************/
//extern void vfbMcsLedServ_vfbOcsLedServ_output(hvfbOcsLedServ t);
//TODO

/*组件输出类实例
***********************************************/
extern vfbOcsLedServ vfbOcsLedServA;


/***********************************************************
* 组件类定义
***********************************************************/
/*组件状态机状态
* 有两个状态init/default，状态list不显示，默认给出
* 状态list需根据实际应用进行重写，list修改后相应状态函数得对应修改
***********************************************/
#define SM_CSLEDSERV_STA_LIST(_) \
    _(smcsLedServ, sta1)\
    _(smcsLedServ, sta2)

/*组件状态机定义
***********************************************/
SMDC(smcsLedServ, SM_CSLEDSERV_STA_LIST)
{
    sta next;
    //TODO

    // 注入组件类
    void *csLedServ;
};


/*组件类声明
***********************************************/
CL(csLedServ){
    hcsLedServ self;
    hcsLedServ (*init)(hcsLedServ cthis, hstaAct smcsLedServ, hvfbOcsLedServ vfbOcsLedServ);

    // 组件运行状态机
    smcsLedServRec smcsLedServRec;
    hstaAct smcsLedServ;

    // 组件运行相关参数
    //TODO

    // 组件运行功能函数
    void (*run)(hcsLedServ t);
    //void (*example)(hcsLedServ t);
    //TODO

    // 组件输入功能函数
    //void (*input)(hcsLedServ t);

    // 组件输出功能函数
    //void (*output)(hcsLedServ t);

    // 注入组件输出类及其他功能类
    INJ(vfbOcsLedServ, vfbOcsLedServ);
};

/*异步调度功能函数
* 命名方式: 存放类+实际类+实际类功能
* 只有cas类型组件才有此函数
***********************************************/
//void csLedServ_abi_example(void);
//TODO

/*组件类实例
***********************************************/
extern csLedServ csLedServA;


/***********************************************************
* 组件输入类定义
***********************************************************/
/*组件输入类声明
***********************************************/
CL(vfbIcsLedServ){
    hvfbIcsLedServ self;
    hvfbIcsLedServ (*init)(hvfbIcsLedServ cthis, hcsLedServ csLedServ);

    // 组件输入类功能函数
    void (*input)(hvfbIcsLedServ t);
    //TODO

    // 注入组件类
    INJ(csLedServ, csLedServ);
};

/*组件输入类实例
***********************************************/
extern vfbIcsLedServ vfbIcsLedServA;


#endif

/**************************** Copyright(C) pxf ****************************/
