/**************************************************************************
* @copyright    :Copyright(C), 2018, pxf, person.
* @file         :cpcFmea.h
* @author       :pxf
* @version      :v1.0
* @date         :2018/09/07 21:33:44
* @brief        :组件cpcFmea 输入类、组件类、输出类数据类型声明头文件
* @others       :
* @history      :180907 pxf 初次建立
***************************************************************************/

#ifndef CPCFMEA_H_
#define CPCFMEA_H_

#include "..\..\01_std\std.h"
#include "..\..\02_bm\fifo\fifo.h"
#include "..\..\06_cas\casSch\casSch.h"
#include "cpcFmeaCfg.h"
#include "cpcFmeaErrCode.h"

/***********************************************************
* 组件初始化
***********************************************************/
/*组件输入初始化
* 输入: 无
* 输出: int16 0-成功,-1-失败
***********************************************/
int16 vfbIcpcFmeaInit(void);

/*组件初始化
* 输入: 无
* 输出: int16 0-成功,-1-失败
***********************************************/
int16 cpcFmeaInit(void);

/*组件输出初始化
* 输入: 无
* 输出: int16 0-成功,-1-失败
***********************************************/
int16 vfbOcpcFmeaInit(void);

/*管理组件初始化外部声明
* 输入: 无
* 输出: int16 0-成功,-1-失败
***********************************************/
extern int16 vfbMcpcFmeaInit(void);


/***********************************************************
* 组件调度
***********************************************************/
/*组件进行调度
* 输入: 无
* 输出: 无
***********************************************/
void cpcFmeaSch(void);


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
CL(vfbOcpcFmea){
    hvfbOcpcFmea self;
    hvfbOcpcFmea (*init)(hvfbOcpcFmea cthis);

    // 组件输出类参数
    schParam schParam;    // 组件调度参数
    //TODO

    // 组件输出类功能函数
    //void (*err)(hvfbOcpcFmea t, herrCode code);
    //void (*output)(hvfbO%s t);
    //TODO
};

/*组件输出类外部接口声明
* 命名方式: 存放类+实际类+实际类功能
***********************************************/
//extern void vfbMcpcFmea_vfbOcpcFmea_err(hvfbOcpcFmea t, herrCode code);
//extern void vfbMcpcFmea_vfbOcpcFmea_output(hvfbOcpcFmea t);
//TODO

/*组件输出类实例
***********************************************/
extern vfbOcpcFmea vfbOcpcFmeaA;


/***********************************************************
* 组件类定义
***********************************************************/
/*组件状态机状态
* 有两个状态init/default，状态list不显示，默认给出
* 状态list需根据实际应用进行重写，list修改后相应状态函数得对应修改
***********************************************/
#define SM_CPCFMEA_STA_LIST(_) \
    _(smcpcFmea, sta1)\
    _(smcpcFmea, sta2)

/*组件状态机声明
***********************************************/
SMDC(smcpcFmea, SM_CPCFMEA_STA_LIST){
    sta next;
    errCode code[CPCFMEA_ERRCODE_FIFO_LEN_CFG];
    fifo errFifo;
    //TODO

    // 注入组件类
    void *cpcFmea;
};


/*组件类声明
***********************************************/
CL(cpcFmea){
    hcpcFmea self;
    hcpcFmea (*init)(hcpcFmea cthis, hstaAct smcpcFmea, hvfbOcpcFmea vfbOcpcFmea,
            void *listBuffer, int16 listBuffSize, int16 fifoObjSize);

    // 组件运行状态机
    smcpcFmeaRec smcpcFmeaRec;
    hstaAct smcpcFmea;

    // 组件运行相关参数
    //TODO

    // 组件运行功能函数
    void (*run)(hcpcFmea t);
    //void (*example)(hcpcFmea t);
    //TODO

    // 组件输入功能函数
    void (*save)(hcpcFmea t, herrCode code);
    //TODO

    // 组件输出功能函数
    //void (*err)(hcpcFmea t, herrCode code);
    //void (*output)(hcpcFmea t);
    //TODO

    // 注入组件输出类及其他功能类
    INJ(vfbOcpcFmea, vfbOcpcFmea);
    EXT(fifo);
};

/*异步调度功能函数
* 命名方式: 存放类+实际类+实际类功能
* 只有cas类型组件才有此函数
***********************************************/
//void cpcFmea_abi_example(void);
//TODO

/*组件类实例
***********************************************/
extern cpcFmea cpcFmeaA;


/***********************************************************
* 组件输入类定义
***********************************************************/
/*组件输入类声明
***********************************************/
CL(vfbIcpcFmea){
    hvfbIcpcFmea self;
    hvfbIcpcFmea (*init)(hvfbIcpcFmea cthis, hcpcFmea cpcFmea);

    // 组件输入类功能函数
    void (*save)(hvfbIcpcFmea t, herrCode code);
    //TODO

    // 注入组件类
    INJ(cpcFmea, cpcFmea);
};

/*组件输入类实例
***********************************************/
extern vfbIcpcFmea vfbIcpcFmeaA;


#endif /* CPCFMEA_H_ */

/**************************** Copyright(C) pxf ****************************/
