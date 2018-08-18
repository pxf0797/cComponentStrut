/*
 * vfbMcasSch.h
 *
 *  Created on: 2018年8月18日
 *      Author: pxf
 */

#ifndef VFBMCASSCH_H_
#define VFBMCASSCH_H_

#include "..\..\06_cas\casSch\casSch.h"

// --------------------------------------------------------------
// 管理组件初始化
// --------------------------------------------------------------
// 管理组件初始化------------------------
int16 vfbMcasSchInit(void);


// --------------------------------------------------------------
// 组件管理类定义
// --------------------------------------------------------------
// 组件管理类声明------------------------
CL(vfbMcasSch)
{
    hvfbMcasSch self;
    hvfbMcasSch (*init)(hvfbMcasSch cthis);

    void (*tickOut)(hvfbMcasSch t);
    void (*err)(hvfbMcasSch t, herrCode code);
};

// 输出类接口声明------------------------
// 接口结构：管理类+组件类+组件类函数
void vfbMcasSch_vfbOcasSch_tickOut(hvfbOcasSch t);
void vfbMcasSch_vfbOcasSch_err(hvfbOcasSch t, herrCode code);

// 组件管理类实例------------------------
extern vfbMcasSch vfbMcasSchA;

#endif /* VFBMCASSCH_H_ */
