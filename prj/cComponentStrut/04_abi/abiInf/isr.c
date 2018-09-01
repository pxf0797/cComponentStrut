/**************************************************************************
* @copyright    :Copyright(C), 2018, pxf, person.
* @file         :isr.c
* @author       :pxf
* @version      :v1.0
* @date         :2018/09/01 16:25:01
* @brief        :线程接口抽象类定义
* @others       :
* @history      :180901 pxf 初次建立
***************************************************************************/

#include "..\abi.h"

/***********************************************************
* 线程接口抽象类定义
***********************************************************/
/*线程接口抽象类初始化函数
* 输入: cthis isr类指针
* 输出: hisr cthis/OOPC_NULL
***********************************************/
hisr isr_init(hisr cthis, void (*isr)(void))
{
    cthis->iIsr.isr = isr;

    return cthis;
}

/*线程接口抽象类构造函数
* 输入: cthis isr类指针
* 输出: hisr cthis/OOPC_NULL
***********************************************/
CC(isr)
{
    cthis->init = isr_init;
    return cthis;
}
/*线程接口抽象类析构函数
* 输入: cthis isr类指针
* 输出: OOPC_RETURN_DATATYPE OOPC_TRUE/OOPC_FALSE
***********************************************/
CD(isr)
{
    return OOPC_TRUE;
}

/**************************** Copyright(C) pxf ****************************/
