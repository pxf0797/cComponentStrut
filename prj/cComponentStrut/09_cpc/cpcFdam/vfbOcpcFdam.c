/*
 * vfbOcpcFdam.c
 *
 *  Created on: 2018年8月18日
 *      Author: pxf
 */

#include "cpcFdam.h"

// --------------------------------------------------------------
// 组件输出初始化
// --------------------------------------------------------------
// 组件输出初始化------------------------
int16 vfbOcpcFdamInit(void)
{
    int16 rtv = 0;

    CNNP(vfbOcpcFdam, &vfbOcpcFdamA);
    if (OPRS(vfbOcpcFdamA) != OOPC_NULL)
    {
        rtv = vfbMcpcFdamInit();
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
hvfbOcpcFdam vfbOcpcFdam_init(hvfbOcpcFdam cthis)
{
    return cthis;
}

CC(vfbOcpcFdam)
{
    cthis->init = vfbOcpcFdam_init;

    return cthis;
}
CD(vfbOcpcFdam)
{
    return OOPC_TRUE;
}

// --------------------------------------------------------------
// 抽象输出类实例化
// --------------------------------------------------------------
vfbOcpcFdam vfbOcpcFdamA;
