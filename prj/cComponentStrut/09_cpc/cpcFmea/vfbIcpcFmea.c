/**************************************************************************
* @copyright    :Copyright(C), 2018, pxf, person.
* @file         :vfbIcpcFmea.c
* @author       :pxf
* @version      :v1.0
* @date         :2018/09/07 21:33:44
* @brief        :组件cpcFmea 输入类定义
* @others       :
* @history      :180907 pxf 初次建立
***************************************************************************/

#include "cpcFmea.h"

/***********************************************************
* 组件输入初始化
***********************************************************/
/*组件输入初始化
* 输入: 无
* 输出: int16 0-成功,-1-失败
***********************************************/
int16 vfbIcpcFmeaInit(void){
    int16 rtv = 0;

    CN(vfbIcpcFmea, &vfbIcpcFmeaA, &cpcFmeaA);
    if(OPRS(vfbIcpcFmeaA) != OOPC_NULL){
        rtv = cpcFmeaInit();
    }else{
        rtv = -1;
    }

    return rtv;
}


/***********************************************************
* 组件输入定义
***********************************************************/
/*组件类初始化函数
* 输入: cthis vfbIcpcFmea类指针
* 输出: hvfbIcpcFmea cthis/OOPC_NULL
***********************************************/
hvfbIcpcFmea vfbIcpcFmea_init(hvfbIcpcFmea cthis, hcpcFmea cpcFmea){
    // 功能函数配置
    //TODO

    // 参数配置
    cthis->cpcFmea = cpcFmea;
    //TODO

    return cthis;
}

/*vfbIcpcFmea_save
* 输入: t vfbIcpcFmea类指针，code errCode指针
* 输出: 无
***********************************************/
void vfbIcpcFmea_save(hvfbIcpcFmea t, herrCode code){
    t->cpcFmea->save(t->cpcFmea, code);
}

/*组件类构造函数
* 输入: cthis vfbIcpcFmea类指针
* 输出: hvfbIcpcFmea cthis/OOPC_NULL
***********************************************/
CC(vfbIcpcFmea){
    // 功能函数配置
    cthis->init = vfbIcpcFmea_init;
    cthis->save = vfbIcpcFmea_save;
    //TODO

    // 参数配置
    //TODO

    return cthis;
}
/*组件类析构函数
* 输入: cthis vfbIcpcFmea类指针
* 输出: OOPC_RETURN_DATATYPE OOPC_TRUE/OOPC_FALSE
***********************************************/
CD(vfbIcpcFmea){
    return OOPC_TRUE;
}


/***********************************************************
* 组件输入实例化
***********************************************************/
/*组件输入类实例
***********************************************/
vfbIcpcFmea vfbIcpcFmeaA;


/**************************** Copyright(C) pxf ****************************/
