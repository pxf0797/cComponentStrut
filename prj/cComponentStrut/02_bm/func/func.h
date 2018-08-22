/*
 * func.h
 *
 *  Created on: 2018年8月21日
 *      Author: pxf
 */

#ifndef FUNC_H_
#define FUNC_H_

#include "..\..\01_std\std.h"

// 低通滤波(Low-pass filter)
// a=0-1，本次滤波结果=(1-a)*本次采样值+a*上次滤波结果
// Y(n) = αX(n)+(1-α)Y(n-1)
// 为了优化计算效率，a只取1/(2^N)，最小值为1/2
// Y(n)= (1/(2^N))X(n)+(1-(1/(2^N)))Y(n-1)
//     = (X(n)+((2^N)-1)Y(n-1))/(2^N)
#define lowpassFilter(newValue, lastValue, n)  (((newValue) + (((lastValue) << (n)) - (lastValue))) >> (n))


#endif /* FUNC_H_ */
