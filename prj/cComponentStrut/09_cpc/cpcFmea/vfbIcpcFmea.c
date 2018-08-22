/*
 * vfbIcpcFmea.c
 *
 *  Created on: 2018年8月22日
 *      Author: pxf
 */

#include "cpcFmea.h"

// --------------------------------------------------------------
// 组件输入初始化
// --------------------------------------------------------------
// 组件输入初始化------------------------
int16 vfbIcpcFmeaInit(void)
{
    int16 rtv = 0;

    CN(vfbIcpcFmea, &vfbIcpcFmeaA, &cpcFmeaA);
    if (OPRS(vfbIcpcFmeaA) != OOPC_NULL)
    {
        rtv = cpcFmeaInit();
    }
    else
    {
        rtv = -1;
    }

    return rtv;
}


// --------------------------------------------------------------
// 抽象输入类定义
// --------------------------------------------------------------
hvfbIcpcFmea vfbIcpcFmea_init(hvfbIcpcFmea cthis, hcpcFmea cpcFmea)
{
    cthis->cpcFmea = cpcFmea;

    return cthis;
}

void vfbIcpcFmea_saveErrCode(hvfbIcpcFmea t, herrCode code)
{
    t->cpcFmea->saveErrCode(t->cpcFmea, code);
}

CC(vfbIcpcFmea)
{
    cthis->init = vfbIcpcFmea_init;
    cthis->saveErrCode = vfbIcpcFmea_saveErrCode;

//    cthis->schParam.id = 0;
//    cthis->schParam.schTask = cpcFmeaSch;
//    cthis->schParam.startTick = (CPCFDAM_START_TICK_CFG / CASSCH_TIMER_PRD_CFG);
//    cthis->schParam.prdTick = (CPCFDAM_PRD_TICK_CFG / CASSCH_TIMER_PRD_CFG);

    return cthis;
}
CD(vfbIcpcFmea)
{
    return OOPC_TRUE;
}

// --------------------------------------------------------------
// 抽象输入类实例化
// --------------------------------------------------------------
vfbIcpcFmea vfbIcpcFmeaA;
