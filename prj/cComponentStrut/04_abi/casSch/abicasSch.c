/*
 * abicasSch.c
 *
 *  Created on: 2018年8月22日
 *      Author: pxf
 */

#include "abicasSch.h"
#include "..\..\03_bsp\bsp.h"
#include "..\..\06_cas\casSch\casSch.h"

// --------------------------------------------------------------
// 组件抽象接口初始化
// --------------------------------------------------------------
int16 abicasSchInit(void)
{
    int16 rtv = 0;

    CN(isr, &timer, casSch_abi_timer);
    if (OPRS(timer) == OOPC_NULL)
    {
        rtv++;
    }
    CN(isr, &mainLoop, casSch_abi_mainLoop);
    if (OPRS(mainLoop) == OOPC_NULL)
    {
        rtv++;
    }

    CN(measure, &time, bspMeasureStart, bspMeasureEnd);
    if (OPRS(time) == OOPC_NULL)
    {
        rtv++;
    }

    return rtv;
}

// --------------------------------------------------------------
// 组件抽象接口
// --------------------------------------------------------------
// 线程类抽象接口------------------------
isr timer;
isr mainLoop;

// 时间测量类抽象接口--------------------
measure time;

