/*
 * vfbOcasSch.c
 *
 *  Created on: 2018年8月18日
 *      Author: pxf
 */

#include "casSch.h"

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
