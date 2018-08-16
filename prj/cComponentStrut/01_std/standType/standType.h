/*************************************************
 * Copyright © person
 * File name    : standType.h
 * Author       : pxf
 * Version      : v1.0
 * Created on   : 2018/8/16
 * Description  : 基本数据类型进行定义
 * Others       : 无
 * History      : 180816 pxf 初次建立
 ************************************************/

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
