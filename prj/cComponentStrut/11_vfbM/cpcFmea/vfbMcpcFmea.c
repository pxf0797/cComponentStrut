/**************************************************************************
* @copyright    :Copyright(C), 2018, pxf, person.
* @file         :vfbMcpcFmea.c
* @author       :pxf
* @version      :v1.0
* @date         :2018/09/07 21:33:44
* @brief        :组件cpcFmea 管理类定义
* @others       :
* @history      :180907 pxf 初次建立
***************************************************************************/

#include "vfbMcpcFmea.h"

/*组件调度id临时配置，组件实际使用时必须在vbfMCfg.h中配置
***********************************************************/
//#define cpcFmea_id_priority_cfg   0


/***********************************************************
* 组件管理初始化
***********************************************************/
/*组件管理初始化
* 输入: 无
* 输出: int16 0-成功,-1-失败
***********************************************/
int16 vfbMcpcFmeaInit(void){
    int16 rtv = 0;

    CN(vfbMcpcFmea, &vfbMcpcFmeaA, &vfbOcpcFmeaA, &vfbIcasSchA);
    if(OPRS(vfbMcpcFmeaA) != OOPC_NULL){
        vfbMcpcFmeaA.vfbOcpcFmea->schParam.id = cpcFmea_id_priority_cfg;
        vfbMcpcFmeaA.vfbOcpcFmea->schParam.prdTick = (CPCFMEA_PRD_TICK_CFG / CASSCH_TIMER_PRD_CFG);
        vfbMcpcFmeaA.vfbOcpcFmea->schParam.startTick = (CPCFMEA_PRD_TICK_CFG / CASSCH_TIMER_PRD_CFG);
        vfbMcpcFmeaA.vfbIcasSch->addTask(vfbMcpcFmeaA.vfbIcasSch,
            vfbMcpcFmeaA.vfbOcpcFmea->schParam.id, vfbMcpcFmeaA.vfbOcpcFmea->schParam.schTask,
            vfbMcpcFmeaA.vfbOcpcFmea->schParam.prdTick, vfbMcpcFmeaA.vfbOcpcFmea->schParam.startTick);

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
* 输入: cthis vfbMcpcFmea类指针
* 输出: hvfbMcpcFmea cthis/OOPC_NULL
***********************************************/
hvfbMcpcFmea vfbMcpcFmea_init(hvfbMcpcFmea cthis, hvfbOcpcFmea vfbOcpcFmea, hvfbIcasSch vfbIcasSch){
    // 功能函数配置
    //TODO

    // 参数配置
    cthis->vfbOcpcFmea = vfbOcpcFmea;
    cthis->vfbIcasSch = vfbIcasSch;
    //TODO

    return cthis;
}

/*组件管理功能函数
* 输入: t vfbMcpcFmea类指针
* 输出: 无
***********************************************/
void vfbMcpcFmea_func(hvfbMcpcFmea t){
    ;
}

/*组件管理类构造函数
* 输入: cthis vfbMcpcFmea类指针
* 输出: hvfbMcpcFmea cthis/OOPC_NULL
***********************************************/
CC(vfbMcpcFmea){
    // 功能函数配置
    cthis->init = vfbMcpcFmea_init;
    //cthis->func = vfbMcpcFmea_func;
    //TODO

    // 参数配置
    //TODO

    return cthis;
}
/*组件管理类析构函数
* 输入: cthis vfbMcpcFmea类指针
* 输出: OOPC_RETURN_DATATYPE OOPC_TRUE/OOPC_FALSE
***********************************************/
CD(vfbMcpcFmea){
    return OOPC_TRUE;
}


/***********************************************************
* 组件输出类接口定义
***********************************************************/
/*组件输出类错误输出函数
***********************************************/
//void vfbMcpcFmea_vfbOcpcFmea_err(hvfbOcpcFmea t, herrCode code){
    //TODO
//}

/*组件输出类功能函数
***********************************************/
//void vfbMcpcFmea_vfbOcpcFmea_output(hvfbOcpcFmea t){
    //TODO
//}


/***********************************************************
* 组件管理实例化
***********************************************************/
/*组件管理类实例
***********************************************/
vfbMcpcFmea vfbMcpcFmeaA;


/**************************** Copyright(C) pxf ****************************/
