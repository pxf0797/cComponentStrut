/**************************************************************************
* @copyright    :Copyright(C), 2018, pxf, person.
* @file         :vfbIcasSch.c
* @author       :pxf
* @version      :v1.0
* @date         :2018/08/31 20:52:28
* @brief        :组件casSch 输入类定义
* @others       :
* @history      :180831 pxf 初次建立
***************************************************************************/

#include "casSch.h"

/***********************************************************
* 组件输入初始化
***********************************************************/
/*组件输入初始化
* 输入: 无
* 输出: int16 0-成功,-1-失败
***********************************************/
int16 vfbIcasSchInit(void){
    int16 rtv = 0;

    CN(vfbIcasSch, &vfbIcasSchA, &casSchA);
    if(OPRS(vfbIcasSchA) != OOPC_NULL){
        rtv = casSchInit();
    }else{
        rtv = -1;
    }

    return rtv;
}


/***********************************************************
* 组件输入定义
***********************************************************/
/*组件类初始化函数
* 输入: cthis vfbIcasSch类指针
* 输出: hvfbIcasSch cthis/OOPC_NULL
***********************************************/
hvfbIcasSch vfbIcasSch_init(hvfbIcasSch cthis, hcasSch casSch){
    // 注入实例配置
    cthis->casSch = casSch;
    //TODO

    return cthis;
}

/*vfbIcasSch_addTask 组件输入添加任务函数
* 输入: cthis vfbIcasSch类指针
* 输出: 无
***********************************************/
void vfbIcasSch_addTask(hvfbIcasSch t, int16 id, void(*schTask)(void), uint16 prdTick, uint16 startTick)
{
    t->casSch->addTask(t->casSch, id, schTask, prdTick, startTick);
}

/*vfbIcasSch_delTask 组件输入删除任务函数
* 输入: cthis vfbIcasSch类指针
* 输出: 无
***********************************************/
void vfbIcasSch_delTask(hvfbIcasSch t, int16 id, void(*schTask)(void))
{
    t->casSch->delTask(t->casSch, id, schTask);
}

/*组件类构造函数
* 输入: cthis vfbIcasSch类指针
* 输出: hvfbIcasSch cthis/OOPC_NULL
***********************************************/
CC(vfbIcasSch){
    // 功能函数配置
    cthis->init = vfbIcasSch_init;
    cthis->addTask = vfbIcasSch_addTask;
    cthis->delTask = vfbIcasSch_delTask;

    return cthis;
}
/*组件类析构函数
* 输入: cthis vfbIcasSch类指针
* 输出: OOPC_RETURN_DATATYPE OOPC_TRUE/OOPC_FALSE
***********************************************/
CD(vfbIcasSch){
    return OOPC_TRUE;
}


/***********************************************************
* 组件输入实例化
***********************************************************/
/*组件输入类实例
***********************************************/
vfbIcasSch vfbIcasSchA;


/**************************** Copyright(C) pxf ****************************/
