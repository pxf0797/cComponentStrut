/*
 * vfbMcpcFmea.c
 *
 *  Created on: 2018年8月22日
 *      Author: pxf
 */

#include "vfbMcpcFmea.h"

// --------------------------------------------------------------
// 管理组件初始化
// --------------------------------------------------------------
// 管理组件初始化------------------------
int16 vfbMcpcFmeaInit(void)
{
    int16 rtv = 0;

    CN(vfbMcpcFmea, &vfbMcpcFmeaA, &vfbOcpcFmeaA, &vfbIcasSchA);
    if (OPRS(vfbMcpcFmeaA) != OOPC_NULL)
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
hvfbMcpcFmea vfbMcpcFmea_init(hvfbMcpcFmea cthis, hvfbOcpcFmea vfbOcpcFmea, hvfbIcasSch vfbIcasSch)
{
    cthis->vfbOcpcFmea = vfbOcpcFmea;
    cthis->vfbIcasSch = vfbIcasSch;

    return cthis;
}

CC(vfbMcpcFmea)
{
    cthis->init = vfbMcpcFmea_init;

    return cthis;
}
CD(vfbMcpcFmea)
{
    return OOPC_TRUE;
}

// --------------------------------------------------------------
// 输出类接口定义
// --------------------------------------------------------------




// --------------------------------------------------------------
// 组件管理类实例
// --------------------------------------------------------------
vfbMcpcFmea vfbMcpcFmeaA;
