/**************************************************************************
* @copyright    :Copyright(C), 2018, pxf, person.
* @file         :vfbMcasSch.h
* @author       :pxf
* @version      :v1.0
* @date         :2018/08/31 20:52:28
* @brief        :组件casSch 管理类数据类型声明
* @others       :
* @history      :180831 pxf 初次建立
***************************************************************************/

#ifndef VFBMCASSCH_H_
#define VFBMCASSCH_H_

#include "../../01_std/std.h"
#include "../../06_cas/casSch/casSch.h"
#include "../vfbMCfg.h"

/***********************************************************
* 组件管理初始化
***********************************************************/
/*组件管理初始化
* 输入: 无
* 输出: int16 0-成功,-1-失败
***********************************************/
int16 vfbMcasSchInit(void);


/***********************************************************
* 组件管理类定义
***********************************************************/
/*组件管理类声明
***********************************************/
CL(vfbMcasSch){
    hvfbMcasSch self;
    hvfbMcasSch (*init)(hvfbMcasSch cthis, hvfbOcasSch vfbOcasSch, hvfbIcasSch vfbIcasSch);

    // 组件管理输出功能函数
    void (*tickOut)(hvfbMcasSch t);
    void (*err)(hvfbMcasSch t, herrCode code);

    // 注入组件输出类及其他功能类
    INJ(vfbOcasSch, vfbOcasSch);
    INJ(vfbIcasSch, vfbIcasSch);
};

/*组件输出类接口声明
* 命名方式: 存放类+实际类+实际类功能
***********************************************/
void vfbMcasSch_vfbOcasSch_tickOut(hvfbOcasSch t);
void vfbMcasSch_vfbOcasSch_err(hvfbOcasSch t, herrCode code);

/*组件管理类实例
***********************************************/
extern vfbMcasSch vfbMcasSchA;


#endif /* VFBMCASSCH_H_ */

/**************************** Copyright(C) pxf ****************************/
