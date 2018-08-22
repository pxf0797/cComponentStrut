/*
 * vfbMcpcFmea.h
 *
 *  Created on: 2018年8月22日
 *      Author: pxf
 */

#ifndef VFBMCPCFMEA_H_
#define VFBMCPCFMEA_H_

#include "..\..\09_cpc\cpcFmea\cpcFmea.h"

// --------------------------------------------------------------
// 管理组件初始化
// --------------------------------------------------------------
// 管理组件初始化------------------------
int16 vfbMcpcFmeaInit(void);



// --------------------------------------------------------------
// 组件管理类定义
// --------------------------------------------------------------
// 组件管理类声明------------------------
CL(vfbMcpcFmea)
{
    hvfbMcpcFmea self;
    hvfbMcpcFmea (*init)(hvfbMcpcFmea cthis, hvfbOcpcFmea vfbOcpcFmea, hvfbIcasSch vfbIcasSch);

    INJ(vfbOcpcFmea, vfbOcpcFmea);
    INJ(vfbIcasSch, vfbIcasSch);
};

// 输出类接口声明------------------------
// 接口结构：管理类+组件类+组件类函数


// 组件管理类实例------------------------
extern vfbMcpcFmea vfbMcpcFmeaA;

#endif /* VFBMCPCFMEA_H_ */
