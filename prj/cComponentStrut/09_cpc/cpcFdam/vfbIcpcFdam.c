/*
 * vfbIcpcFdam.c
 *
 *  Created on: 2018年8月18日
 *      Author: pxf
 */

#include "cpcFdam.h"

// --------------------------------------------------------------
// 组件输入初始化
// --------------------------------------------------------------
// 组件输入初始化------------------------
int16 vfbIcpcFdamInit(void)
{
    int16 rtv = 0;

    CN(vfbIcpcFdam, &vfbIcpcFdamA, &cpcFdamA);
    if (OPRS(vfbIcpcFdamA) != OOPC_NULL)
    {
        rtv = cpcFdamInit();
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
hvfbIcpcFdam vfbIcpcFdam_init(hvfbIcpcFdam cthis, hcpcFdam cpcFdam)
{
    cthis->cpcFdam = cpcFdam;

    return cthis;
}

void vfbIcpcFdam_saveErrCode(hvfbIcpcFdam t, herrCode code)
{
    t->cpcFdam->saveErrCode(t->cpcFdam, code);
}

CC(vfbIcpcFdam)
{
    cthis->init = vfbIcpcFdam_init;
    cthis->saveErrCode = vfbIcpcFdam_saveErrCode;

    return cthis;
}
CD(vfbIcpcFdam)
{
    return OOPC_TRUE;
}

// --------------------------------------------------------------
// 抽象输入类实例化
// --------------------------------------------------------------
vfbIcpcFdam vfbIcpcFdamA;
