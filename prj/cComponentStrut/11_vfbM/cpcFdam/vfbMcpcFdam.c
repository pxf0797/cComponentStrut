/*
 * vfbMcpcFdam.c
 *
 *  Created on: 2018年8月18日
 *      Author: pxf
 */

#include "vfbMcpcFdam.h"

// --------------------------------------------------------------
// 管理组件初始化
// --------------------------------------------------------------
// 管理组件初始化------------------------
int16 vfbMcpcFdamInit(void)
{
    int16 rtv = 0;

    CNNP(vfbMcpcFdam, &vfbMcpcFdamA);
    if (OPRS(vfbMcpcFdamA) != OOPC_NULL)
    {
        rtv = 0;
    }
    else
    {
        rtv = -1;
    }

    return rtv;
}



// --------------------------------------------------------------
// 组件管理类定义
// --------------------------------------------------------------
hvfbMcpcFdam vfbMcpcFdam_init(hvfbMcpcFdam cthis)
{
    return cthis;
}

CC(vfbMcpcFdam)
{
    cthis->init = vfbMcpcFdam_init;

    return cthis;
}
CD(vfbMcpcFdam)
{
    return OOPC_TRUE;
}

// --------------------------------------------------------------
// 输出类接口定义
// --------------------------------------------------------------




// --------------------------------------------------------------
// 组件管理类实例
// --------------------------------------------------------------
vfbMcpcFdam vfbMcpcFdamA;
