/*
 * measure.c
 *
 *  Created on: 2018Äê8ÔÂ17ÈÕ
 *      Author: pxf
 */

#include "..\abi.h"

hmeasure measure_init(hmeasure cthis, void (*start)(uint32 *point), uint32 (*end)(uint32 point))
{
    cthis->iMeasure.start = start;
    cthis->iMeasure.end = end;

    return cthis;
}

CC(measure)
{
    cthis->init = measure_init;
    return cthis;
}

CD(measure)
{
    return OOPC_TRUE;
}

