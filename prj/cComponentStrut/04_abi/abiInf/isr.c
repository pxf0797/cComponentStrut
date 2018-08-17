/*
 * isr.c
 *
 *  Created on: 2018Äê8ÔÂ17ÈÕ
 *      Author: pxf
 */

#include "..\abi.h"

hisr isr_init(hisr cthis, void (*isr)(void))
{
    cthis->iIsr.isr = isr;

    return cthis;
}

CC(isr)
{
    cthis->init = isr_init;
    return cthis;
}

CD(isr)
{
    return OOPC_TRUE;
}
