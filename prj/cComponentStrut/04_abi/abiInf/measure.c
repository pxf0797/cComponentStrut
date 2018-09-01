/**************************************************************************
* @copyright    :Copyright(C), 2018, pxf, person.
* @file         :measure.c
* @author       :pxf
* @version      :v1.0
* @date         :2018/09/01 16:25:01
* @brief        :测量接口抽象类定义
* @others       :
* @history      :180901 pxf 初次建立
***************************************************************************/

#include "..\abi.h"

/***********************************************************
* 测量接口抽象类定义
***********************************************************/
/*测量接口抽象类初始化函数
* 输入: cthis measure类指针
* 输出: hmeasure cthis/OOPC_NULL
***********************************************/
hmeasure measure_init(hmeasure cthis, void (*start)(uint32 *point), uint32 (*end)(uint32 point))
{
    cthis->iMeasure.start = start;
    cthis->iMeasure.end = end;

    return cthis;
}

/*测量接口抽象类构造函数
* 输入: cthis measuer类指针
* 输出: hmeasure cthis/OOPC_NULL
***********************************************/
CC(measure)
{
    cthis->init = measure_init;
    return cthis;
}
/*测量接口抽象类析构函数
* 输入: cthis measure类指针
* 输出: OOPC_RETURN_DATATYPE OOPC_TRUE/OOPC_FALSE
***********************************************/
CD(measure)
{
    return OOPC_TRUE;
}

/**************************** Copyright(C) pxf ****************************/
