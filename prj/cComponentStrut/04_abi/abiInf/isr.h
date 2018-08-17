/*
 * isr.h
 *
 *  Created on: 2018Äê8ÔÂ17ÈÕ
 *      Author: pxf
 */

#ifndef ISR_H_
#define ISR_H_

CL(isr)
{
    hisr self;
    hisr (*init)(hisr cthis, void (*isr)(void));

    IMPL(iIsr);
};

#endif /* ISR_H_ */
