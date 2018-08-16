/*************************************************
 * Copyright © person
 * File name    : fifo.c
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

#include "fifo.h"

// 文件内函数声明-------------------------------------------------
static int16 fifo_push(hfifo t, void *data);
static int16 fifo_pop(hfifo t, void *data);
static int16 fifo_fout(hfifo t, void *data);
static int16 fifo_del(hfifo t, void *data);
static hfifo fifo_init(hfifo cthis, void *listBuffer, int16 listBuffSize, int16 fifoObjSize);

/*************************************************
 * Function     : fifo_push()
 * Description  : 函数压入存储对象到队列中
 * Calls        : 无
 * Called By    : fifo_ctor()
 * Input        : t - 队列类指针
 *                data - 存储到队列中存储对象，大小由t->fifoObjSize定义
 * Output       : TRUE/FALSE
 * Return       : 返回值返回类型为int16，0成功，1队列已满，2队列正忙，3失败
 * Others       : 无
 ************************************************/
static int16 fifo_push(hfifo t, void *data)
{
    int16 rtv = 0;
    int8 *srcPtr = (int8 *)data;
    int8 *desPtr = NULL;
    int16 i = 0;

    if (t->fifoOpSta == 0)
    {
        t->fifoOpSta = 1;

        if (t->currLen < t->saveObjMaxLen)
        {
            // 计算存储位置并存储
            desPtr = (t->listBuffer + (t->top * t->fifoObjSize));
            for (i = 0; i < t->fifoObjSize; i++)
            {
                *desPtr++ = *srcPtr++;
            }

            // 更新标志
            t->currLen++;
            t->top++;
            if (t->top >= t->saveObjMaxLen)
            {
                t->top = 0;
            }
            else
            {
                ;
            }

            rtv = 0;
        }
        else
        {
            rtv = 1;
        }

        t->fifoOpSta = 0;
    }
    else
    {
        // 正在操作队列情况下，数据存入备用缓存
        if (t->rsvdBuffSta == 0)
        {
            t->rsvdBuffSta = 1;

            // 计算存储位置并存储
            desPtr = (t->listBuffer + (t->saveObjMaxLen * t->fifoObjSize));
            for (i = 0; i < t->fifoObjSize; i++)
            {
                *desPtr++ = *srcPtr++;
            }

            rtv = 2;
        }
        else
        {
            rtv = 3;
        }
    }

    return rtv;
}

/*************************************************
 * Function     : fifo_pop()
 * Description  : 函数从对列中弹出最一个进入对列中的存储对象
 * Calls        : 无
 * Called By    : fifo_ctor()
 * Input        : t - 队列类指针
 *                data - 存储到队列中对象，大小由t->fifoObjSize定义
 * Output       : TRUE/FALSE
 * Return       : 返回值返回类型为int16，0成功，1队列为空，2队列正忙，3失败
 * Others       : 无
 ************************************************/
static int16 fifo_pop(hfifo t, void *data)
{
    int16 rtv = 0;
    int8 *srcPtr = NULL;
    int8 *desPtr = (int8 *)data;
    int16 i = 0;

    if (t->fifoOpSta == 0)
    {
        t->fifoOpSta = 1;

        if (t->currLen > 0)
        {
            // 更新标志
            t->currLen--;
            t->top--;
            if (t->top <= 0)
            {
                t->top = (t->saveObjMaxLen - 1);
            }
            else
            {
                ;
            }

            // 计算存储位置并读取数据
            srcPtr = (t->listBuffer + (t->top * t->fifoObjSize));
            for (i = 0; i < t->fifoObjSize; i++)
            {
                *desPtr++ = *srcPtr++;
            }

            rtv = 0;
        }
        else
        {
            rtv = 1;
        }

        t->fifoOpSta = 0;

        // 退出时查看备用缓存是否有数据
        if (t->rsvdBuffSta == 1)
        {
            t->rsvdBuffSta = 0;
            if (0 != t->push(t, (t->listBuffer + (t->saveObjMaxLen * t->fifoObjSize))))
            {
                // 在操作失败情况下，才更改返回状态
                rtv = 3;
            }
            else
            {
                ;
            }
        }
        else
        {
            ;
        }
    }
    else
    {
        rtv = 2;
    }

    return rtv;
}

/*************************************************
 * Function     : fifo_fout()
 * Description  : 函数从对列中获取第一个进入对列中的存储对象
 * Calls        : 无
 * Called By    : fifo_ctor()
 * Input        : t - 队列类指针
 *                data - 存储到队列中对象，大小由t->fifoObjSize定义
 * Output       : TRUE/FALSE
 * Return       : 返回值返回类型为int16，0成功，1队列为空，2队列正忙，3失败
 * Others       : 无
 ************************************************/
static int16 fifo_fout(hfifo t, void *data)
{
    int16 rtv = 0;
    int8 *srcPtr = NULL;
    int8 *desPtr = (int8 *)data;
    int16 i = 0;

    if (t->fifoOpSta == 0)
    {
        t->fifoOpSta = 1;

        if (t->currLen > 0)
        {
            // 计算存储位置并存储
            srcPtr = (t->listBuffer + (t->bottom * t->fifoObjSize));
            for (i = 0; i < t->fifoObjSize; i++)
            {
                *desPtr++ = *srcPtr++;
            }

            // 更新标志
            t->currLen--;
            t->bottom++;
            if (t->bottom >= t->saveObjMaxLen)
            {
                t->bottom = 0;
            }
            else
            {
                ;
            }

            rtv = 0;
        }
        else
        {
            rtv = 1;
        }

        t->fifoOpSta = 0;

        // 退出时查看备用缓存是否有数据
        if (t->rsvdBuffSta == 1)
        {
            t->rsvdBuffSta = 0;
            if (0 != t->push(t, (t->listBuffer + (t->saveObjMaxLen * t->fifoObjSize))))
            {
                // 在操作失败情况下，才更改返回状态
                rtv = 3;
            }
            else
            {
                ;
            }
        }
        else
        {
            ;
        }
    }
    else
    {
        rtv = 2;
    }

    return rtv;
}

/*************************************************
 * Function     : fifo_del()
 * Description  : 函数从队列中删除某类存储对象
 * Calls        : 无
 * Called By    : fifo_ctor()
 * Input        : t - 队列类指针
 *                data - 存储到队列中对象，大小由t->fifoObjSize定义
 * Output       : TRUE/FALSE
 * Return       : 返回值返回类型为int16，0成功，1未找到数据，2队列正忙，3失败
 * Others       : 无
 ************************************************/
static int16 fifo_del(hfifo t, void *data)
{
    int16 rtv = 0;
    int8 *srcPtr = (int8 *)data;
    int8 *desPtr = (t->listBuffer + (t->saveObjMaxLen * t->fifoObjSize));
    int16 i = 0;
    int16 j = t->currLen;
    int16 lastMaxLen = t->currLen;

    if (t->fifoOpSta == 0)
    {
        if (t->currLen > 0)
        {
            // 全队列查找数据，找到就删除
            for (j = t->currLen; j > 0; j--)
            {
                // 读取数据
                if (0 == t->fout(t, desPtr))
                {
                    // 判断数据是否相同，相同则删除，不同则存回队列
                    srcPtr = (int8 *)data;
                    for (i = 0; i < t->fifoObjSize; i++)
                    {
                        if (*desPtr++ != *srcPtr++)
                        {
                            break;
                        }
                        else
                        {
                            ;
                        }
                    }

                    if (i < t->fifoObjSize)
                    {
                        // 非查找数据存回队列
                        if (0 != t->push(t, desPtr))
                        {
                            rtv = 3;
                        }
                        else
                        {
                            rtv = 1;
                        }
                    }
                    else
                    {
                        rtv = 1;
                    }
                }
                else
                {
                    rtv = 3;
                }

                if (3 == rtv)
                {
                    break;
                }
                else
                {
                    ;
                }
            }

            // 判断是否找到并删除数据，并返回操作结果
            if ((1 == rtv) && (t->currLen < lastMaxLen))
            {
                // 找到则更改状态为成功
                rtv = 0;
            }
            else
            {
                ;
            }
        }
        else
        {
            rtv = 1;
        }
    }
    else
    {
        rtv = 2;
    }

    return rtv;
}

/*************************************************
 * Function     : fifo_init()
 * Description  : 函数为队列类进行参数初始化
 * Calls        : 无
 * Called By    : fifo_ctor()
 * Input        : t - 队列类指针
 *                data - 存储到队列中对象，大小由t->fifoObjSize定义
 * Output       : cthis/OOPC_NULL
 * Return       : 返回值返回类型为hFifo，当前只返回cthis/OOPC_NULL
 * Others       : 无
 ************************************************/
static hfifo fifo_init(hfifo cthis, void *listBuffer, int16 listBuffSize, int16 fifoObjSize)
{
    cthis->listBuffer = (int8 *)listBuffer;
    cthis->listBuffSize = listBuffSize;
    cthis->fifoObjSize = fifoObjSize;

    cthis->saveObjMaxLen = ((cthis->listBuffSize / cthis->fifoObjSize) - 1);

    return cthis;
}

/*************************************************
 * Function     : fifo_ctor()
 * Description  : 队列类实例化时的构造函数
 * Calls        : 无
 * Called By    : fifo_new()
 * Input        : cthis - 队列类指针
 * Output       : cthis/OOPC_NULL
 * Return       : 返回值返回类型为hFifo，当前只返回cthis/OOPC_NULL
 * Others       : 无
 ************************************************/
CC(fifo)
{
    cthis->init = fifo_init;
    cthis->push = fifo_push;
    cthis->pop = fifo_pop;
    cthis->fout = fifo_fout;
    cthis->del = fifo_del;

    cthis->listBuffer = NULL;
    cthis->listBuffSize = 0;
    cthis->fifoObjSize = 0;

    cthis->saveObjMaxLen = 0;
    cthis->currLen = 0;
    cthis->top = 0;
    cthis->bottom = 0;

    cthis->fifoOpSta = 0;
    cthis->rsvdBuffSta = 0;

    return cthis;
}

/*************************************************
 * Function     : fifo_dtor()
 * Description  : 队列类内存释放时的析构函数
 * Calls        : 无
 * Called By    : fifo_delete()
 * Input        : cthis - 队列类指针
 * Output       : OOPC_TRUE/OOPC_FALSE
 * Return       : 返回值返回类型为int，当前只返回OOPC_TRUE/OOPC_FALSE
 * Others       : 无
 ************************************************/
CD(fifo)
{
    return OOPC_TRUE;
}
