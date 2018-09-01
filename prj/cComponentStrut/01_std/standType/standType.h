/**************************************************************************
* @copyright    :Copyright(C), 2018, pxf, person.
* @file         :standType.h
* @author       :pxf
* @version      :v1.0
* @date         :2018/09/01 14:40:50
* @brief        :基本数据类型进行定义
* @others       :
* @history      :180901 pxf 初次建立
***************************************************************************/

#ifndef STANDTYPE_H_
#define STANDTYPE_H_

// 基本数据类型定义
#ifndef FALSE
#define FALSE    0
#endif
#ifndef TRUE
#define TRUE     1
#endif
#ifndef NULL
#define NULL     ((void *)0)
#endif

// 整型
typedef char                  int8;
typedef short                 int16;
typedef long                  int32;
typedef long long             int64;

// 无符整型
typedef unsigned char         uint8;
typedef unsigned short        uint16;
typedef unsigned long         uint32;
typedef unsigned long long    uint64;

// 浮点
typedef float                 float32;
typedef double                float64;

#endif /* STANDTYPE_H_ */

/**************************** Copyright(C) pxf ****************************/
