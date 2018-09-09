/**************************************************************************
* @copyright    :Copyright(C), 2018, pxf, person.
* @file         :gi.c
* @author       :pxf
* @version      :v1.0
* @date         :2018/09/01 16:25:01
* @brief        :GIO输入接口抽象类定义
* @others       :
* @history      :180901 pxf 初次建立
***************************************************************************/

#include "../abi.h"

/***********************************************************
* GIO输入接口抽象类定义
***********************************************************/
/*GIO输入接口抽象类初始化函数
* 输入: cthis gi类指针
* 输出: hgi cthis/OOPC_NULL
***********************************************/
hgi gi_init(hgi cthis, uint16 (*get)(void)){
    cthis->iGi.get = get;

    return cthis;
}

/*GIO输入接口抽象类构造函数
* 输入: cthis gi类指针
* 输出: hgi cthis/OOPC_NULL
***********************************************/
CC(gi){
    cthis->init = gi_init;
    return cthis;
}
/*GIO输入接口抽象类析构函数
* 输入: cthis gi类指针
* 输出: OOPC_RETURN_DATATYPE OOPC_TRUE/OOPC_FALSE
***********************************************/
CD(gi){
    return OOPC_TRUE;
}

/**************************** Copyright(C) pxf ****************************/
