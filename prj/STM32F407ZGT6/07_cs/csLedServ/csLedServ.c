/**************************************************************************
* @copyright    :Copyright(C), 2018, pxf, person.
* @file         :csLedServ.c
* @author       :pxf
* @version      :v1.0
* @date         :2018/09/07 22:42:51
* @brief        :组件csLedServ 组件类定义
* @others       :
* @history      :180907 pxf 初次建立
***************************************************************************/

#include "csLedServ.h"
#include "../../04_abi/csLedServ/abicsLedServ.h"

/***********************************************************
* 组件初始化
***********************************************************/
/*组件初始化
* 输入: 无
* 输出: int16 0-成功,-1-失败
***********************************************/
int16 csLedServInit(void){
    int16 rtv = 0;

    CN(csLedServ, &csLedServA, &smcsLedServ[0], &vfbOcsLedServA);
    if(OPRS(csLedServA) != OOPC_NULL){
        rtv = vfbOcsLedServInit();
    }else{
        rtv = -1;
    }

    return rtv;
}


/***********************************************************
* 组件调度
***********************************************************/
/*组件进行调度
* 输入: 无
* 输出: 无
***********************************************/
void csLedServSch(void){
    csLedServA.run(csLedServA.self);
}


/***********************************************************
* 组件通用功能函数
***********************************************************/


/***********************************************************
* 组件状态机
***********************************************************/
/*组件状态机定义
***********************************************/
SMDF(smcsLedServ, SM_CSLEDSERV_STA_LIST);

/*smcsLedServ_act_init
* 输入: hStaRec 状态记录结构体指针
* 输出: 无
***********************************************/
void smcsLedServ_act_init(void *hStaRec){
    hsmcsLedServRec rec = (hsmcsLedServRec)hStaRec;

    rec->csLedServ = (void *)&csLedServA;
    //TODO

    rec->next = smcsLedServ_sta_default;
}

/*smcsLedServ_act_sta1
* 输入: hStaRec 状态记录结构体指针
* 输出: 无
***********************************************/
void smcsLedServ_act_sta1(void *hStaRec){
    hsmcsLedServRec rec = (hsmcsLedServRec)hStaRec;
    //((hcsLedServ)(rec->csLedServ))->
    //TODO

    rec->next = smcsLedServ_sta_default;
}

/*smcsLedServ_act_sta2
* 输入: hStaRec 状态记录结构体指针
* 输出: 无
***********************************************/
void smcsLedServ_act_sta2(void *hStaRec){
    hsmcsLedServRec rec = (hsmcsLedServRec)hStaRec;
    //((hcsLedServ)(rec->csLedServ))->
    //TODO

    rec->next = smcsLedServ_sta_default;
}

/*smcsLedServ_act_default
* 输入: hStaRec 状态记录结构体指针
* 输出: 无
***********************************************/
void smcsLedServ_act_default(void *hStaRec){
    hsmcsLedServRec rec = (hsmcsLedServRec)hStaRec;
    //((hcsLedServ)(rec->csLedServ))->
    //TODO

    rec->next = smcsLedServ_sta_default;
}


/***********************************************************
* 组件定义
***********************************************************/
/*组件类初始化函数
* 输入: cthis csLedServ类指针
* 输出: hcsLedServ cthis/OOPC_NULL
***********************************************/
hcsLedServ csLedServ_init(hcsLedServ cthis, hstaAct smcsLedServ, hvfbOcsLedServ vfbOcsLedServ){
    // 功能函数配置
    //TODO

    // 参数配置
    cthis->smcsLedServ = smcsLedServ;
    cthis->vfbOcsLedServ = vfbOcsLedServ;
    //TODO

    return cthis;
}

/*组件运行函数
* 输入: t csLedServ类指针
* 输出: 无
***********************************************/
void csLedServ_run(hcsLedServ t){
    SMRE(t->smcsLedServ, t->smcsLedServRec);
}

/*组件错误输出函数
* 输入: t csLedServ类指针
* 输出: 无
***********************************************/
void csLedServ_err(hcsLedServ t, herrCode code){
    t->vfbOcsLedServ->err(t->vfbOcsLedServ, code);
}

/*组件类构造函数
* 输入: cthis csLedServ类指针
* 输出: hcsLedServ cthis/OOPC_NULL
***********************************************/
CC(csLedServ){
    // 功能函数配置
    cthis->init = csLedServ_init;
    cthis->run = csLedServ_run;
    cthis->err = csLedServ_err;
    //TODO

    // 参数配置
    cthis->smcsLedServRec.next = smcsLedServ_sta_init;
    //TODO

    return cthis;
}
/*组件类析构函数
* 输入: cthis csLedServ类指针
* 输出: OOPC_RETURN_DATATYPE OOPC_TRUE/OOPC_FALSE
***********************************************/
CD(csLedServ){
    return OOPC_TRUE;
}


/***********************************************************
* 组件异步调度功能函数
***********************************************************/
/*异步调度功能函数
***********************************************/
//void csLedServ_abi_example(void){
    //TODO
//}


/***********************************************************
* 组件实例化
***********************************************************/
/*组件类实例
***********************************************/
csLedServ csLedServA;


/**************************** Copyright(C) pxf ****************************/
