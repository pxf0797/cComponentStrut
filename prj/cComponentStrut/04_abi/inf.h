/*
 * inf.h
 *
 *  Created on: 2018年8月17日
 *      Author: pxf
 */

#ifndef INF_H_
#define INF_H_

// 线程类接口
INF(iIsr)
{
    void (*isr)(void);
};

// 时间测量接口
INF(iMeasure)
{
    void (*start)(uint32 *point);
    uint32 (*end)(uint32 point);
};

// GIO输入输出接口
INF(iGi)
{
    uint16 (*get)(void);
};
INF(iGo)
{
    void (*set)(uint16 sw);
};



#endif /* INF_H_ */
