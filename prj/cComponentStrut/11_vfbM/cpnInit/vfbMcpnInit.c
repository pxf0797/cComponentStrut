/*
 * vfbMcpnInit.c
 *
 *  Created on: 2018年8月18日
 *      Author: pxf
 */

#include "vfbMcpnInit.h"
#include "..\..\04_abi\abi.h"
#include "..\..\06_cas\casSch\casSch.h"

// --------------------------------------------------------------
// 管理组件初始化
// --------------------------------------------------------------
int16 vfbMcpnInit(void)
{
    int16 rtv = 0;

    rtv |= vfbIabiInit();
    rtv |= vfbIcasSchInit();

    return rtv;
}

