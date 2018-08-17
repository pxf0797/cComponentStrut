/*
 * measure.h
 *
 *  Created on: 2018Äê8ÔÂ17ÈÕ
 *      Author: pxf
 */

#ifndef MEASURE_H_
#define MEASURE_H_

CL(measure)
{
    hmeasure self;
    hmeasure (*init)(hmeasure cthis, void (*start)(uint32 *point), uint32 (*end)(uint32 point));

    IMPL(iMeasure);
};

#endif /* MEASURE_H_ */
