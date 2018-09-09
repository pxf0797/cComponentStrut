/**************************************************************************
* @copyright    :Copyright(C), 2018, pxf, person.
* @file         :measure.h
* @author       :pxf
* @version      :v1.0
* @date         :2018/09/01 16:25:01
* @brief        :测量接口抽象类声明
* @others       :
* @history      :180901 pxf 初次建立
***************************************************************************/

#ifndef MEASURE_H_
#define MEASURE_H_

/***********************************************************
* 测量接口抽象类定义
***********************************************************/
/*测量接口抽象类声明声明
***********************************************/
CL(measure)
{
    hmeasure self;
    hmeasure (*init)(hmeasure cthis, void (*start)(uint32 *point), uint32 (*end)(uint32 point));

    IMPL(iMeasure);
};

#endif /* MEASURE_H_ */

/**************************** Copyright(C) pxf ****************************/
