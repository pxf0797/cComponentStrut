/*
 * vfbOcasSch.c
 *
 *  Created on: 2018年8月18日
 *      Author: pxf
 */

#include "casSch.h"

// --------------------------------------------------------------
// 组件输出初始化
// --------------------------------------------------------------
// 组件输出初始化------------------------
int16 vfbOcasSchInit(void)
{
    int16 rtv = 0;

    CN(vfbOcasSch, &vfbOcasSchA, vfbMcasSch_vfbOcasSch_tickOut, vfbMcasSch_vfbOcasSch_err);
    if (OPRS(vfbOcasSchA) != OOPC_NULL)
    {
        rtv = vfbMcasSchInit();
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
hvfbOcasSch vfbOcasSch_init(hvfbOcasSch cthis,
        void (*tickOut)(hvfbOcasSch t),
        void (*err)(hvfbOcasSch t, herrCode code))
{
    cthis->tickOut = tickOut;
    cthis->err = err;

    return cthis;
}

CC(vfbOcasSch)
{
    cthis->init = vfbOcasSch_init;

    return cthis;
}
CD(vfbOcasSch)
{
    return OOPC_TRUE;
}

// --------------------------------------------------------------
// 抽象输出类实例化
// --------------------------------------------------------------
vfbOcasSch vfbOcasSchA;
