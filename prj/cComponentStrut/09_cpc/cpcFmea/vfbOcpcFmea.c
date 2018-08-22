/*
 * vfbOcpcFmea.c
 *
 *  Created on: 2018年8月22日
 *      Author: pxf
 */

#include "cpcFmea.h"

// --------------------------------------------------------------
// 组件输出初始化
// --------------------------------------------------------------
// 组件输出初始化------------------------
int16 vfbOcpcFmeaInit(void)
{
    int16 rtv = 0;

    CNNP(vfbOcpcFmea, &vfbOcpcFmeaA);
    if (OPRS(vfbOcpcFmeaA) != OOPC_NULL)
    {
        rtv = vfbMcpcFmeaInit();
    }
    else
    {
        rtv = -1;
    }

    return rtv;
}


// --------------------------------------------------------------
// 抽象输出类定义
// --------------------------------------------------------------
hvfbOcpcFmea vfbOcpcFmea_init(hvfbOcpcFmea cthis)
{
    return cthis;
}

CC(vfbOcpcFmea)
{
    cthis->init = vfbOcpcFmea_init;

    cthis->schParam.id = 0;
    cthis->schParam.schTask = cpcFmeaSch;
    cthis->schParam.startTick = (CPCFMEA_START_TICK_CFG / CASSCH_TIMER_PRD_CFG);
    cthis->schParam.prdTick = (CPCFMEA_PRD_TICK_CFG / CASSCH_TIMER_PRD_CFG);

    return cthis;
}
CD(vfbOcpcFmea)
{
    return OOPC_TRUE;
}

// --------------------------------------------------------------
// 抽象输出类实例化
// --------------------------------------------------------------
vfbOcpcFmea vfbOcpcFmeaA;
