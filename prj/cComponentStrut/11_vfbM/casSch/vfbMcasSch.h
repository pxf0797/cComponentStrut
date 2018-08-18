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
// 组件管理类定义
// --------------------------------------------------------------
// 组件管理类声明------------------------
CL(vfbMcasSch)
{
    hvfbMcasSch self;
    hvfbMcasSch (*init)(hvfbMcasSch cthis, hcasSch casSch);

    void (*tickOut)(hvfbMcasSch t);
    void (*err)(hvfbMcasSch t, herrCode code);

    INJ(casSch, casSch);
};

// 输出类接口声明------------------------
// 接口结构：管理类+组件类+组件类函数
void vfbMcasSch_vfbOcasSch_tickOut(hvfbOcasSch t);
void vfbMcasSch_vfbOcasSch_err(hvfbOcasSch t, herrCode code);

// 组件管理类实例------------------------
extern vfbMcasSch vfbMcasSchA;

#endif /* VFBMCASSCH_H_ */
