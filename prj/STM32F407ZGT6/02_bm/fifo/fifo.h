/*************************************************
 * Copyright © person
 * File name    : fifo.h
 * Author       : pxf
 * Version      : v1.0
 * Created on   : 2018/3/9
 * Description  : 本文件内定义了队列类；
 *                队列主要提供以下几个功能：
 *                1.队列存储数据使用push函数
 *                2.队列使用堆栈功能弹出后进数据使用pop函数
 *                3.队列获取先进数据使用fout函数
 *                4.队列还提供某类数据删除功能使用del函数
 * Others       : 无
 * History      : 180309 pxf 初次建立
 ************************************************/

#ifndef FIFO_H_
#define FIFO_H_

#include "../../01_std/std.h"

// 版本定义---------------------------------------------------------------------
#define FIFO_CLASS_VERSION        0xC01D00    // C代表v，D代表.，版本v1.00

// Fifo类定义-------------------------------------------------------------------
CL(fifo)
{
    hfifo self;
    hfifo (*init)(hfifo cthis, void *listBuffer, int16 listBuffSize, int16 fifoObjSize);

    int8 *listBuffer;                                         // 缓存队列起始地址
    int16 listBuffSize;                                       // 缓存队列总大小
    int16 fifoObjSize;                                        // 缓存队列的缓存对象大小

    int16 saveObjMaxLen;                                      // 缓存队列缓存缓存对象的最大个数
                                                              // 由于最后一个作为备用缓存，当前最大个数比实际给入小1
    int16 currLen;                                            // 缓存队列已缓存缓存对象个数
    int16 top;                                                // 空缓存存储指针，此指针是空位置，队列满除外
    int16 bottom;                                             // 最开始缓存对象进来的存放位置，指针有数据

    int16 fifoOpSta;                                          // 队列操作状态，0空闲，1正在操作
    int16 rsvdBuffSta;                                        // 备用缓存是否存在数据，0无数据，1有数据

    // 队列可以多进，但必须单出，即可以多个地方使用push，但pop或fout使用地方只能有一个
    int16 (*push)(hfifo t, void *data);                       // 入列，返回值0成功，1队列已满，2队列正忙，3失败
                                                              // 存在正在读取操作情况下，数据会存入队列最后个备用缓存区，操作完成自动存入队列
    int16 (*pop)(hfifo t, void *data);                        // 最后入列数据出列，返回值0成功，1队列为空，2队列正忙，3失败
    int16 (*fout)(hfifo t, void *data);                       // 最先入列数据出列，first out，返回值0成功，1队列为空，2队列正忙，3失败
    int16 (*del)(hfifo t, void *data);                        // 删除队列中所有存在的某个数据；返回值0成功，1未找到数据，2队列正忙，3失败
};

#endif /* FIFO_H_ */

/**************************** Copyright(C) pxf ****************************/
