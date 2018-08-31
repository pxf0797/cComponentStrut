/**************************************************************************
* @copyright    :Copyright(C), 2018, pxf, person.
* @file         :vfbOcasSch.c
* @author       :pxf
* @version      :v1.0
* @date         :2018/08/31 20:52:28
* @brief        :组件casSch 输出类定义
* @others       :
* @history      :180831 pxf 初次建立
***************************************************************************/

#include "casSch.h"

/***********************************************************
* 组件输出初始化
***********************************************************/
/*组件输入初始化
* 输入: 无
* 输出: int16 0-成功,-1-失败
***********************************************/
int16 vfbOcasSchInit(void){
    int16 rtv = 0;

    CN(vfbOcasSch, &vfbOcasSchA, vfbMcasSch_vfbOcasSch_tickOut, vfbMcasSch_vfbOcasSch_err);
    if(OPRS(vfbOcasSchA) != OOPC_NULL){
        rtv = vfbMcasSchInit();
    }else{
        rtv = -1;
    }

    return rtv;
}


/***********************************************************
* 组件输出定义
***********************************************************/
/*组件类初始化函数
* 输入: cthis vfbOcasSch类指针
* 输出: hvfbOcasSch cthis/OOPC_NULL
***********************************************/
hvfbOcasSch vfbOcasSch_init(hvfbOcasSch cthis,
        void (*tickOut)(hvfbOcasSch t),
        void (*err)(hvfbOcasSch t, herrCode code)){
	// 输出参数配置	
    cthis->tickOut = tickOut;
    cthis->err = err;

    return cthis;
}

/*组件类构造函数
* 输入: cthis vfbOcasSch类指针
* 输出: hvfbOcasSch cthis/OOPC_NULL
***********************************************/
CC(vfbOcasSch){
    // 功能函数配置
    cthis->init = vfbOcasSch_init;
    //TODO

    return cthis;
}
/*组件类析构函数
* 输入: cthis vfbOcasSch类指针
* 输出: OOPC_RETURN_DATATYPE OOPC_TRUE/OOPC_FALSE
***********************************************/
CD(vfbOcasSch){
    return OOPC_TRUE;
}


/***********************************************************
* 组件输出实例化
***********************************************************/
/*组件输出类实例
***********************************************/
vfbOcasSch vfbOcasSchA;


/**************************** Copyright(C) pxf ****************************/
