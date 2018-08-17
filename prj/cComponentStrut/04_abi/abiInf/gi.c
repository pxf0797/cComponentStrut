/*
 * gi.c
 *
 *  Created on: 2018Äê8ÔÂ17ÈÕ
 *      Author: pxf
 */

#include "..\abi.h"

hgi gi_init(hgi cthis, uint16 (*get)(void))
{
    cthis->iGi.get = get;

    return cthis;
}

CC(gi)
{
    cthis->init = gi_init;
    return cthis;
}

CD(gi)
{
    return OOPC_TRUE;
}
