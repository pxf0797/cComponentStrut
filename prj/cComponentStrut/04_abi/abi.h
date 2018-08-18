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

// --------------------------------------------------------------
// 组件初始化
// --------------------------------------------------------------
// 组件输入初始化------------------------
int16 vfbIabiInit(void);

// 组件初始化----------------------------
int16 abiInit(void);

// 组件输出初始化------------------------




// 线程类抽象接口
extern isr timer;
extern isr mainLoop;

// 时间测量类抽象接口
extern measure time;

// 输入类抽象接口
extern gi err;

// 输出类抽象接口
extern go led;






#endif /* ABI_H_ */
