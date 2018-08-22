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
// 组件抽象接口包含
// --------------------------------------------------------------
#include ".\casSch\abicasSch.h"
#include ".\csLedServ\abicsLedServ.h"

// --------------------------------------------------------------
// 组件初始化
// --------------------------------------------------------------
// 组件输入初始化------------------------
int16 vfbIabiInit(void);

// 组件初始化----------------------------
int16 abiInit(void);

// 组件输出初始化------------------------

#endif /* ABI_H_ */
