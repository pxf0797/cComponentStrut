/**************************************************************************
* @copyright    :Copyright(C), 2018, pxf, person.
* @file         :vfbOcsLedServ.c
* @author       :pxf
* @version      :v1.0
* @date         :2018/09/07 22:42:51
* @brief        :组件csLedServ 输出类定义
* @others       :
* @history      :180907 pxf 初次建立
***************************************************************************/

#include "csLedServ.h"

/***********************************************************
* 组件输出初始化
***********************************************************/
/*组件输入初始化
* 输入: 无
* 输出: int16 0-成功,-1-失败
***********************************************/
int16 vfbOcsLedServInit(void){
    int16 rtv = 0;

    CN(vfbOcsLedServ, &vfbOcsLedServA, vfbMcsLedServ_vfbOcsLedServ_err);
    if(OPRS(vfbOcsLedServA) != OOPC_NULL){
        rtv = vfbMcsLedServInit();
    }else{
        rtv = -1;
    }

    return rtv;
}


/***********************************************************
* 组件输出定义
***********************************************************/
/*组件类初始化函数
* 输入: cthis vfbOcsLedServ类指针
* 输出: hvfbOcsLedServ cthis/OOPC_NULL
***********************************************/
hvfbOcsLedServ vfbOcsLedServ_init(hvfbOcsLedServ cthis, void (*err)(hvfbOcsLedServ t, herrCode code)){
    // 功能函数配置
    cthis->err = err;
    //cthis->output = output;
    //TODO

    // 参数配置
    //TODO

    return cthis;
}

/*组件类构造函数
* 输入: cthis vfbOcsLedServ类指针
* 输出: hvfbOcsLedServ cthis/OOPC_NULL
***********************************************/
CC(vfbOcsLedServ){
    // 功能函数配置
    cthis->init = vfbOcsLedServ_init;
    //TODO

    // 参数配置
    cthis->schParam.id = 0;
    cthis->schParam.schTask = csLedServSch;
    cthis->schParam.startTick = (CSLEDSERV_START_TICK_CFG / CASSCH_TIMER_PRD_CFG);
    cthis->schParam.prdTick = (CSLEDSERV_PRD_TICK_CFG / CASSCH_TIMER_PRD_CFG);
    //TODO

    return cthis;
}
/*组件类析构函数
* 输入: cthis vfbOcsLedServ类指针
* 输出: OOPC_RETURN_DATATYPE OOPC_TRUE/OOPC_FALSE
***********************************************/
CD(vfbOcsLedServ){
    return OOPC_TRUE;
}


/***********************************************************
* 组件输出实例化
***********************************************************/
/*组件输出类实例
***********************************************/
vfbOcsLedServ vfbOcsLedServA;


/**************************** Copyright(C) pxf ****************************/
