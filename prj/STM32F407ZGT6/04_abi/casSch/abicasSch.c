/**************************************************************************
* @copyright    :Copyright(C), 2018, pxf, person.
* @file         :abicasSch.c
* @author       :pxf
* @version      :v1.0
* @date         :2018/08/31 20:52:28
* @brief        :组件casSch 抽象接口类定义
* @others       :
* @history      :180831 pxf 初次建立
***************************************************************************/

#include "abicasSch.h"
#include "../../03_bsp/bsp.h"

/***********************************************************
* 组件抽象接口初始化
***********************************************************/
/*组件抽象接口初始化
* 输入: 无
* 输出: int16 0-成功,-1-失败
***********************************************/
int16 abicasSchInit(void){
    int16 rtv = 0;

    CN(isr, &timer, casSch_abi_timer);
    if(OPRS(timer) == OOPC_NULL){
        rtv++;
    }
    CN(isr, &mainLoop, casSch_abi_mainLoop);
    if(OPRS(mainLoop) == OOPC_NULL){
        rtv++;
    }
    CN(measure, &time, bspMeasureStart, bspMeasureEnd);
    if(OPRS(time) == OOPC_NULL){
        rtv++;
    }

    return rtv;
}


/***********************************************************
* 组件抽象接口实例
***********************************************************/
/*线程类抽象实例
***********************************************/
isr timer;
isr mainLoop;

/*时间测量类抽象实例
***********************************************/
measure time;

/**************************** Copyright(C) pxf ****************************/
