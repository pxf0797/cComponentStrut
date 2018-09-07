/**************************************************************************
* @copyright    :Copyright(C), 2018, pxf, person.
* @file         :cpcFmea.c
* @author       :pxf
* @version      :v1.0
* @date         :2018/09/07 21:33:44
* @brief        :组件cpcFmea 组件类定义
* @others       :
* @history      :180907 pxf 初次建立
***************************************************************************/

#include "cpcFmea.h"

/***********************************************************
* 组件初始化
***********************************************************/
/*组件初始化
* 输入: 无
* 输出: int16 0-成功,-1-失败
***********************************************/
int16 cpcFmeaInit(void){
    int16 rtv = 0;

    CN(cpcFmea, &cpcFmeaA, &smcpcFmea[0], &vfbOcpcFmeaA,
            &cpcFmeaA.smcpcFmeaRec.code, sizeof(cpcFmeaA.smcpcFmeaRec.code), sizeof(errCode));
    if(OPRS(cpcFmeaA) != OOPC_NULL){
        rtv = vfbOcpcFmeaInit();
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
void cpcFmeaSch(void){
    cpcFmeaA.run(cpcFmeaA.self);
}


/***********************************************************
* 组件通用功能函数
***********************************************************/


/***********************************************************
* 组件状态机
***********************************************************/
/*组件状态机定义
***********************************************/
SMDF(smcpcFmea, SM_CPCFMEA_STA_LIST);

/*smcpcFmea_act_init
* 输入: hStaRec 状态记录结构体指针
* 输出: 无
***********************************************/
void smcpcFmea_act_init(void *hStaRec){
    hsmcpcFmeaRec rec = (hsmcpcFmeaRec)hStaRec;

    rec->cpcFmea = (void *)&cpcFmeaA;
    //TODO

    rec->next = smcpcFmea_sta_default;
}

/*smcpcFmea_act_sta1
* 输入: hStaRec 状态记录结构体指针
* 输出: 无
***********************************************/
void smcpcFmea_act_sta1(void *hStaRec){
    hsmcpcFmeaRec rec = (hsmcpcFmeaRec)hStaRec;
    //((hcpcFmea)(rec->cpcFmea))->
    //TODO

    rec->next = smcpcFmea_sta_default;
}

/*smcpcFmea_act_sta2
* 输入: hStaRec 状态记录结构体指针
* 输出: 无
***********************************************/
void smcpcFmea_act_sta2(void *hStaRec){
    hsmcpcFmeaRec rec = (hsmcpcFmeaRec)hStaRec;
    //((hcpcFmea)(rec->cpcFmea))->
    //TODO

    rec->next = smcpcFmea_sta_default;
}

/*smcpcFmea_act_default
* 输入: hStaRec 状态记录结构体指针
* 输出: 无
***********************************************/
void smcpcFmea_act_default(void *hStaRec){
    hsmcpcFmeaRec rec = (hsmcpcFmeaRec)hStaRec;
    //((hcpcFmea)(rec->cpcFmea))->
    //TODO

    rec->next = smcpcFmea_sta_default;
}


/***********************************************************
* 组件定义
***********************************************************/
/*组件类初始化函数
* 输入: cthis cpcFmea类指针
* 输出: hcpcFmea cthis/OOPC_NULL
***********************************************/
hcpcFmea cpcFmea_init(hcpcFmea cthis, hstaAct smcpcFmea, hvfbOcpcFmea vfbOcpcFmea,
        void *listBuffer, int16 listBuffSize, int16 fifoObjSize){
    // 功能函数配置
    CCC(fifo, &cthis->smcpcFmeaRec.errFifo, listBuffer, listBuffSize, fifoObjSize);
    if(OPRS(*cthis->fifo) == OOPC_NULL){
        return OOPC_NULL;
    }
    //TODO

    // 参数配置
    cthis->smcpcFmea = smcpcFmea;
    cthis->vfbOcpcFmea = vfbOcpcFmea;
    //TODO

    return cthis;
}

/*组件运行函数
* 输入: t cpcFmea类指针
* 输出: 无
***********************************************/
void cpcFmea_run(hcpcFmea t){
    SMRE(t->smcpcFmea, t->smcpcFmeaRec);
}

/*cpcFmea_save
* 输入: t cpcFmea类指针
* 输出: 无
***********************************************/
void cpcFmea_save(hcpcFmea t, herrCode code){
    t->fifo->push(t->fifo, code);
}

/*组件错误输出函数
* 输入: t cpcFmea类指针
* 输出: 无
***********************************************/
//void cpcFmea_err(hcpcFmea t, herrCode code){
//    t->vfbOcpcFmea->err(t->vfbOcpcFmea, code);
//}

/*组件类构造函数
* 输入: cthis cpcFmea类指针
* 输出: hcpcFmea cthis/OOPC_NULL
***********************************************/
CC(cpcFmea){
    // 功能函数配置
    cthis->init = cpcFmea_init;
    cthis->run = cpcFmea_run;
    //cthis->err = cpcFmea_err;
    //TODO

    // 参数配置
    cthis->smcpcFmeaRec.next = smcpcFmea_sta_init;

    //TODO

    return cthis;
}
/*组件类析构函数
* 输入: cthis cpcFmea类指针
* 输出: OOPC_RETURN_DATATYPE OOPC_TRUE/OOPC_FALSE
***********************************************/
CD(cpcFmea){
    return OOPC_TRUE;
}


/***********************************************************
* 组件异步调度功能函数
***********************************************************/
/*异步调度功能函数
***********************************************/
//void cpcFmea_abi_example(void){
    //TODO
//}


/***********************************************************
* 组件实例化
***********************************************************/
/*组件类实例
***********************************************/
cpcFmea cpcFmeaA;


/**************************** Copyright(C) pxf ****************************/
