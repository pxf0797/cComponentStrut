/*
 * abi.c
 *
 *  Created on: 2018年8月17日
 *      Author: pxf
 */

#include "abi.h"
#include "..\06_cas\casSch\casSch.h"
#include "..\03_bsp\bsp.h"

// 线程类抽象接口
isr timer;
isr mainLoop;

// 时间测量类抽象接口
measure time;

// 输入类抽象接口
gi err;

// 输出类抽象接口
go led;



void abiInit(void)
{
    int16 abiInitErr = 0;

    CN(isr, &timer, abi_casSch_timer);
    if (OPRS(timer) == OOPC_NULL)
    {
        abiInitErr++;
    }
    CN(isr, &mainLoop, abi_casSch_mainLoop);
    if (OPRS(mainLoop) == OOPC_NULL)
    {
        abiInitErr++;
    }

    CN(measure, &time, bspMeasureStart, bspMeasureEnd);
    if (OPRS(time) == OOPC_NULL)
    {
        abiInitErr++;
    }

    CN(gi, &err, bspGiErr);
    if (OPRS(err) == OOPC_NULL)
    {
        abiInitErr++;
    }

    CN(go, &led, bspGoLed);
    if (OPRS(led) == OOPC_NULL)
    {
        abiInitErr++;
    }

}


