/**************************************************************************
* @copyright    :Copyright(C), 2018, pxf, person.
* @file         :go.c
* @author       :pxf
* @version      :v1.0
* @date         :2018/09/01 16:25:01
* @brief        :GIO输出接口抽象类定义
* @others       :
* @history      :180901 pxf 初次建立
***************************************************************************/

#include "../abi.h"

/***********************************************************
* GIO输出接口抽象类定义
***********************************************************/
/*GIO输出接口抽象类初始化函数
* 输入: cthis go类指针
* 输出: hgo cthis/OOPC_NULL
***********************************************/
hgo go_init(hgo cthis, void (*set)(uint16 sw)){
    cthis->iGo.set = set;

    return cthis;
}

/*GIO输出接口抽象类构造函数
* 输入: cthis go类指针
* 输出: hgo cthis/OOPC_NULL
***********************************************/
CC(go){
    cthis->init = go_init;
    return cthis;
}
/*GIO输入接口抽象类析构函数
* 输入: cthis go类指针
* 输出: OOPC_RETURN_DATATYPE OOPC_TRUE/OOPC_FALSE
***********************************************/
CD(go){
    return OOPC_TRUE;
}

/**************************** Copyright(C) pxf ****************************/
