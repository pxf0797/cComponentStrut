/*
 * vfbMcpcFdam.h
 *
 *  Created on: 2018年8月18日
 *      Author: pxf
 */

#ifndef VFBMCPCFDAM_H_
#define VFBMCPCFDAM_H_

#include "..\..\09_cpc\cpcFdam\cpcFdam.h"

// --------------------------------------------------------------
// 管理组件初始化
// --------------------------------------------------------------
// 管理组件初始化------------------------
int16 vfbMcpcFdamInit(void);



// --------------------------------------------------------------
// 组件管理类定义
// --------------------------------------------------------------
// 组件管理类声明------------------------
CL(vfbMcpcFdam)
{
    hvfbMcpcFdam self;
    hvfbMcpcFdam (*init)(hvfbMcpcFdam cthis);

    INJ(cpcFdam, cpcFdam);
};

// 输出类接口声明------------------------
// 接口结构：管理类+组件类+组件类函数


// 组件管理类实例------------------------
extern vfbMcpcFdam vfbMcpcFdamA;

#endif /* VFBMCPCFDAM_H_ */
