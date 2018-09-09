/**************************************************************************
* @copyright    :Copyright(C), 2018, pxf, person.
* @file         :vfbMcsLedServ.c
* @author       :pxf
* @version      :v1.0
* @date         :2018/09/07 22:42:51
* @brief        :组件csLedServ 管理类定义
* @others       :
* @history      :180907 pxf 初次建立
***************************************************************************/

#include "vfbMcsLedServ.h"

/*组件调度id临时配置，组件实际使用时必须在vbfMCfg.h中配置
***********************************************************/
#define csLedServ_id_priority_cfg   0


/***********************************************************
* 组件管理初始化
***********************************************************/
/*组件管理初始化
* 输入: 无
* 输出: int16 0-成功,-1-失败
***********************************************/
int16 vfbMcsLedServInit(void){
    int16 rtv = 0;

    CN(vfbMcsLedServ, &vfbMcsLedServA, &vfbOcsLedServA, &vfbIcasSchA, &vfbIcpcFmeaA);
    if(OPRS(vfbMcsLedServA) != OOPC_NULL){
        vfbMcsLedServA.vfbOcsLedServ->schParam.id = csLedServ_id_priority_cfg;
        vfbMcsLedServA.vfbOcsLedServ->schParam.prdTick = (CSLEDSERV_PRD_TICK_CFG / CASSCH_TIMER_PRD_CFG);
        vfbMcsLedServA.vfbOcsLedServ->schParam.startTick = (CSLEDSERV_PRD_TICK_CFG / CASSCH_TIMER_PRD_CFG);
        vfbMcsLedServA.vfbIcasSch->addTask(vfbMcsLedServA.vfbIcasSch,
            vfbMcsLedServA.vfbOcsLedServ->schParam.id, vfbMcsLedServA.vfbOcsLedServ->schParam.schTask,
            vfbMcsLedServA.vfbOcsLedServ->schParam.prdTick, vfbMcsLedServA.vfbOcsLedServ->schParam.startTick);

        rtv = 0;
    }else{
        rtv = -1;
    }

    return rtv;
}


/***********************************************************
* 组件管理定义
***********************************************************/
/*组件管理类初始化函数
* 输入: cthis vfbMcsLedServ类指针
* 输出: hvfbMcsLedServ cthis/OOPC_NULL
***********************************************/
hvfbMcsLedServ vfbMcsLedServ_init(hvfbMcsLedServ cthis, hvfbOcsLedServ vfbOcsLedServ,
            hvfbIcasSch vfbIcasSch, hvfbIcpcFmea vfbIcpcFmea){
    // 功能函数配置
    //TODO

    // 参数配置
    cthis->vfbOcsLedServ = vfbOcsLedServ;
    cthis->vfbIcasSch = vfbIcasSch;
    cthis->vfbIcpcFmea = vfbIcpcFmea;
    //TODO

    return cthis;
}

/*组件管理功能函数
* 输入: t vfbMcsLedServ类指针
* 输出: 无
***********************************************/
void vfbMcsLedServ_func(hvfbMcsLedServ t){
    ;
}

/*组件管理类构造函数
* 输入: cthis vfbMcsLedServ类指针
* 输出: hvfbMcsLedServ cthis/OOPC_NULL
***********************************************/
CC(vfbMcsLedServ){
    // 功能函数配置
    cthis->init = vfbMcsLedServ_init;
    //cthis->func = vfbMcsLedServ_func;
    //TODO

    // 参数配置
    //TODO

    return cthis;
}
/*组件管理类析构函数
* 输入: cthis vfbMcsLedServ类指针
* 输出: OOPC_RETURN_DATATYPE OOPC_TRUE/OOPC_FALSE
***********************************************/
CD(vfbMcsLedServ){
    return OOPC_TRUE;
}


/***********************************************************
* 组件输出类接口定义
***********************************************************/
/*组件输出类错误输出函数
***********************************************/
void vfbMcsLedServ_vfbOcsLedServ_err(hvfbOcsLedServ t, herrCode code){
    vfbMcsLedServA.vfbIcpcFmea->save(vfbMcsLedServA.vfbIcpcFmea, code);
}

/*组件输出类功能函数
***********************************************/
//void vfbMcsLedServ_vfbOcsLedServ_output(hvfbOcsLedServ t){
    //TODO
//}


/***********************************************************
* 组件管理实例化
***********************************************************/
/*组件管理类实例
***********************************************/
vfbMcsLedServ vfbMcsLedServA;


/**************************** Copyright(C) pxf ****************************/
