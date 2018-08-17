/*
 * basic.c
 *
 *  Created on: 2018Äê8ÔÂ17ÈÕ
 *      Author: pxf
 */

#include "bsp.h"
#include "..\04_abi\abi.h"

void bspInit(void)
{}
void bspTimer_bsp(void)
{
    timer.iIsr.isr();
}
void bspMainLoop_bsp(void)
{
    mainLoop.iIsr.isr();
}


void bspMeasureStart(uint32 *point)
{}
uint32 bspMeasureEnd(uint32 point)
{
    return 0;
}

