/**************************************************************************
* @copyright    :Copyright(C), 2018, pxf, person.
* @file         :vfbMcasSch.c
* @author       :pxf
* @version      :v1.0
* @date         :2018/08/31 20:52:28
* @brief        :组件casSch 管理类定义
* @others       :
* @history      :180831 pxf 初次建立
***************************************************************************/

#include "vfbMcasSch.h"
#include "..\..\07_cs\csLedServ\csLedServ.h"
#include "..\..\09_cpc\cpcFmea\cpcFmea.h"

/*组件调度id临时配置，组件实际使用时必须在vbfMCfg.h中配置
***********************************************************/
//#define casSch_id_priority_cfg   0


/***********************************************************
* 组件管理初始化
***********************************************************/
/*组件管理初始化
* 输入: 无
* 输出: int16 0-成功,-1-失败
***********************************************/
int16 vfbMcasSchInit(void){
    int16 rtv = 0;

    CN(vfbMcasSch, &vfbMcasSchA, &vfbOcasSchA, &vfbIcasSchA);
    if(OPRS(vfbMcasSchA) != OOPC_NULL){
        rtv |= vfbIcsLedServInit();
        rtv |= vfbIcpcFmeaInit();
        //TODO 对其他组件进行初始化

        rtv = 0;
    }else{
        rtv = -1;
    }

    return rtv;
}


/***********************************************************
* 组件管理定义
***********************************************************/
/*组件管理类初始化函数
* 输入: cthis vfbMcasSch类指针
* 输出: hvfbMcasSch cthis/OOPC_NULL
***********************************************/
hvfbMcasSch vfbMcasSch_init(hvfbMcasSch cthis, hvfbOcasSch vfbOcasSch, hvfbIcasSch vfbIcasSch){
    // 注入实例配置
    cthis->vfbOcasSch = vfbOcasSch;
    cthis->vfbIcasSch = vfbIcasSch;
    //TODO

    return cthis;
}

/*hvfbMcasSch_tickOut 节拍输出
* 输入: cthis vfbMcasSch类指针
* 输出: 无
***********************************************/
void vfbMcasSch_tickOut(hvfbMcasSch t)
{}

/*hvfbMcasSch_err 错误输出
* 输入: cthis vfbMcasSch类指针
* 输出: 无
***********************************************/
void vfbMcasSch_err(hvfbMcasSch t, herrCode code)
{}

/*组件管理类构造函数
* 输入: cthis vfbMcasSch类指针
* 输出: hvfbMcasSch cthis/OOPC_NULL
***********************************************/
CC(vfbMcasSch){
    // 功能函数配置
    cthis->init = vfbMcasSch_init;
    cthis->tickOut = vfbMcasSch_tickOut;
    cthis->err = vfbMcasSch_err;

    return cthis;
}
/*组件管理类析构函数
* 输入: cthis vfbMcasSch类指针
* 输出: OOPC_RETURN_DATATYPE OOPC_TRUE/OOPC_FALSE
***********************************************/
CD(vfbMcasSch){
    return OOPC_TRUE;
}


/***********************************************************
* 组件输出类接口定义
***********************************************************/
/*组件输出类功能函数
***********************************************/
void vfbMcasSch_vfbOcasSch_tickOut(hvfbOcasSch t){}
void vfbMcasSch_vfbOcasSch_err(hvfbOcasSch t, herrCode code){}


/***********************************************************
* 组件管理实例化
***********************************************************/
/*组件管理类实例
***********************************************/
vfbMcasSch vfbMcasSchA;


/**************************** Copyright(C) pxf ****************************/
