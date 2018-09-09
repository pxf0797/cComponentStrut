/**************************************************************************
* @copyright    :Copyright(C), 2018, pxf, person.
* @file         :vfbMcpcFmea.h
* @author       :pxf
* @version      :v1.0
* @date         :2018/09/07 21:33:44
* @brief        :组件cpcFmea 管理类数据类型声明
* @others       :
* @history      :180907 pxf 初次建立
***************************************************************************/

#ifndef VFBMCPCFMEA_H_
#define VFBMCPCFMEA_H_

#include "../../01_std/std.h"
#include "../../06_cas/casSch/casSch.h"
#include "../../09_cpc/cpcFmea/cpcFmea.h"
#include "../vfbMCfg.h"

/***********************************************************
* 组件管理初始化
***********************************************************/
/*组件管理初始化
* 输入: 无
* 输出: int16 0-成功,-1-失败
***********************************************/
int16 vfbMcpcFmeaInit(void);


/***********************************************************
* 组件管理类定义
***********************************************************/
/*组件管理类声明
***********************************************/
CL(vfbMcpcFmea){
    hvfbMcpcFmea self;
    hvfbMcpcFmea (*init)(hvfbMcpcFmea cthis, hvfbOcpcFmea vfbOcpcFmea, hvfbIcasSch vfbIcasSch);

    // 组件管理参数
    //TODO

    // 组件管理功能函数
    //void (*func)(hvfbMcpcFmea t);
    //TODO

    // 注入组件输出类及其他功能类
    INJ(vfbOcpcFmea, vfbOcpcFmea);
    INJ(vfbIcasSch, vfbIcasSch);
};

/*组件输出类接口声明
* 命名方式: 存放类+实际类+实际类功能
***********************************************/
//void vfbMcpcFmea_vfbOcpcFmea_err(hvfbOcpcFmea t, herrCode code);
//void vfbMcpcFmea_vfbOcpcFmea_output(hvfbOcpcFmea t);

/*组件管理类实例
***********************************************/
extern vfbMcpcFmea vfbMcpcFmeaA;


#endif /* VFBMCPCFMEA_H_ */

/**************************** Copyright(C) pxf ****************************/
