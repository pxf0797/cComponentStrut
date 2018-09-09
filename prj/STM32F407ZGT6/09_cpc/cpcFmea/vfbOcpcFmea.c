/**************************************************************************
* @copyright    :Copyright(C), 2018, pxf, person.
* @file         :vfbOcpcFmea.c
* @author       :pxf
* @version      :v1.0
* @date         :2018/09/07 21:33:44
* @brief        :组件cpcFmea 输出类定义
* @others       :
* @history      :180907 pxf 初次建立
***************************************************************************/

#include "cpcFmea.h"

/***********************************************************
* 组件输出初始化
***********************************************************/
/*组件输入初始化
* 输入: 无
* 输出: int16 0-成功,-1-失败
***********************************************/
int16 vfbOcpcFmeaInit(void){
    int16 rtv = 0;

    CNNP(vfbOcpcFmea, &vfbOcpcFmeaA);
    if(OPRS(vfbOcpcFmeaA) != OOPC_NULL){
        rtv = vfbMcpcFmeaInit();
    }else{
        rtv = -1;
    }

    return rtv;
}


/***********************************************************
* 组件输出定义
***********************************************************/
/*组件类初始化函数
* 输入: cthis vfbOcpcFmea类指针
* 输出: hvfbOcpcFmea cthis/OOPC_NULL
***********************************************/
hvfbOcpcFmea vfbOcpcFmea_init(hvfbOcpcFmea cthis){
    // 功能函数配置
    //cthis->err = err;
    //cthis->output = output;
    //TODO

    // 参数配置
    //TODO

    return cthis;
}

/*组件类构造函数
* 输入: cthis vfbOcpcFmea类指针
* 输出: hvfbOcpcFmea cthis/OOPC_NULL
***********************************************/
CC(vfbOcpcFmea){
    // 功能函数配置
    cthis->init = vfbOcpcFmea_init;
    //TODO

    // 参数配置
    cthis->schParam.id = 0;
    cthis->schParam.schTask = cpcFmeaSch;
    cthis->schParam.startTick = (CPCFMEA_START_TICK_CFG / CASSCH_TIMER_PRD_CFG);
    cthis->schParam.prdTick = (CPCFMEA_PRD_TICK_CFG / CASSCH_TIMER_PRD_CFG);
    //TODO

    return cthis;
}
/*组件类析构函数
* 输入: cthis vfbOcpcFmea类指针
* 输出: OOPC_RETURN_DATATYPE OOPC_TRUE/OOPC_FALSE
***********************************************/
CD(vfbOcpcFmea){
    return OOPC_TRUE;
}


/***********************************************************
* 组件输出实例化
***********************************************************/
/*组件输出类实例
***********************************************/
vfbOcpcFmea vfbOcpcFmeaA;


/**************************** Copyright(C) pxf ****************************/
