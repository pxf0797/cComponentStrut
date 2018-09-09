/*
 * basic.h
 *
 *  Created on: 2018Äê8ÔÂ17ÈÕ
 *      Author: pxf
 */

#ifndef BASIC_H_
#define BASIC_H_

void bspStaticInit(void);
void bspTimer(void);
void bspMainLoop(void);

void bspMeasureStart(uint32 *point);
uint32 bspMeasureEnd(uint32 point);

#endif /* BASIC_H_ */
