/*
 * vfbMcasSch.c
 *
 *  Created on: 2018年8月18日
 *      Author: pxf
 */

#include "vfbMcasSch.h"

// --------------------------------------------------------------
// 组件管理类定义
// --------------------------------------------------------------
hvfbMcasSch hvfbMcasSch_init(hvfbMcasSch cthis, hcasSch casSch)
{
    cthis->casSch = casSch;

    return cthis;
}

void hvfbMcasSch_tickOut(hvfbMcasSch t)
{}
void hvfbMcasSch_err(hvfbMcasSch t, herrCode code)
{}

CC(vfbMcasSch)
{
    cthis->init = hvfbMcasSch_init;
    cthis->tickOut = hvfbMcasSch_tickOut;
    cthis->err = hvfbMcasSch_err;

    return cthis;
}
CD(vfbMcasSch)
{
    return OOPC_TRUE;
}

// --------------------------------------------------------------
// 输出类接口定义
// --------------------------------------------------------------
void vfbMcasSch_vfbOcasSch_tickOut(hvfbOcasSch t)
{}
void vfbMcasSch_vfbOcasSch_err(hvfbOcasSch t, herrCode code)
{}

// --------------------------------------------------------------
// 组件管理类实例
// --------------------------------------------------------------
vfbMcasSch vfbMcasSchA;
