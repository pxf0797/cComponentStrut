/*
 * abi.h
 *
 *  Created on: 2018年8月17日
 *      Author: pxf
 */

#ifndef ABI_H_
#define ABI_H_

// 包含接口进行分类
#include "..\01_std\std.h"

#include "inf.h"

#include ".\abiInf\isr.h"
#include ".\abiInf\measure.h"

#include ".\abiInf\gi.h"
#include ".\abiInf\go.h"


// 线程类抽象接口
extern isr timer;
extern isr mainLoop;

// 时间测量类抽象接口
extern measure time;

// 输入类抽象接口
extern gi err;

// 输出类抽象接口
extern go led;




// 抽象接口进行初始化
void abiInit(void);

#endif /* ABI_H_ */
