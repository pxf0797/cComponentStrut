/**************************************************************************
* @copyright    :Copyright(C), 2018, pxf, person.
* @file         :casSch.c
* @author       :pxf
* @version      :v1.0
* @date         :2018/08/31 20:52:28
* @brief        :组件casSch 组件类定义
* @others       :
* @history      :180831 pxf 初次建立
***************************************************************************/

#include "casSch.h"
#include "..\..\02_bm\func\func.h"

/***********************************************************
* 组件初始化
***********************************************************/
/*组件初始化
* 输入: 无
* 输出: int16 0-成功,-1-失败
***********************************************/
int16 casSchInit(void){
    int16 rtv = 0;

    CN(casSch, &casSchA, &smcasSch[0], &vfbOcasSchA, &time);
    if(OPRS(casSchA) != OOPC_NULL){
        rtv = vfbOcasSchInit();
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
//void casSchSch(void){
//    casSchA.run(casSchA.self);
//}


/***********************************************************
* 组件通用功能函数
***********************************************************/
/*schTaskDefault默认任务
* 输入: hStaRec 状态记录结构体指针
* 输出: 无
***********************************************/
static void schTaskDefault(void){}

/*log_2n 纯粹求2^n的对应的对数n
* 输入: hStaRec 状态记录结构体指针
* 输出: 无
***********************************************/
static inline int16 log_2n(uint32 num){
    int16 n = 0;

    if((num & 0xFFFF0000U) != 0U){
        n += 16;
    }
    if((num & 0xFF00FF00U) != 0U){
        n += 8;
    }
    if((num & 0xF0F0F0F0U) != 0U){
        n += 4;
    }
    if ((num & 0xCCCCCCCCU) != 0U){
        n += 2;
    }
    if ((num & 0xAAAAAAAAU) != 0U){
        n += 1;
    }

    return n;
}

/***********************************************************
* 组件状态机
***********************************************************/
/*组件状态机定义
***********************************************/
SMDF(smcasSch, SM_CASSCH_STA_LIST);

/*smcasSch_act_init
* 输入: hStaRec 状态记录结构体指针
* 输出: 无
***********************************************/
void smcasSch_act_init(void *hStaRec){
    hsmcasSchRec rec = (hsmcasSchRec)hStaRec;

    rec->casSch = (void *)&casSchA;
    rec->next = smcasSch_sta_update;
}

/*smcasSch_sta_update
* 输入: hStaRec 状态记录结构体指针
* 输出: 无
***********************************************/
void smcasSch_act_update(void *hStaRec){
    hsmcasSchRec rec = (hsmcasSchRec)hStaRec;
    //((hcasSch)(rec->casSch))->
    uint32 taskMask = 0;
    uint32 curTask = 0;
    int16 taskIndex = 0;
    int16 i = 0;

    for(i = 0; i < rec->task.taskGroupNum; i++){
        // 更新各组激活任务
        taskMask = rec->task.taskMask[i];
        while(taskMask != 0){
            curTask = (taskMask & (taskMask ^ (taskMask - 1)));
            taskMask ^= curTask;
            taskIndex = log_2n(curTask);

            if((rec->task.tick - rec->task.startTick[i][taskIndex]) >= rec->task.prdTick[i][taskIndex]){
                // 更新激活状态以及下一激活起始节拍
                rec->task.actMask[i] |= curTask;
                rec->task.startTick[i][taskIndex] += rec->task.prdTick[i][taskIndex];
            }
        }
    }

    // 所有任务更新后进入执行状态查看是否有要执行任务
    rec->next = smcasSch_sta_execute;
}

/*smcasSch_act_execute
* 输入: hStaRec 状态记录结构体指针
* 输出: 无
***********************************************/
void smcasSch_act_execute(void *hStaRec){
    hsmcasSchRec rec = (hsmcasSchRec)hStaRec;
    //((hcasSch)(rec->casSch))->
    uint32 taskMask = 0;
    uint32 curTask = 0;
    int16 taskIndex = 0;
    int16 i = 0;
    errCode errcode;
#if (CASSCH_TASK_MEASURE_ENABLE == 1)
    static uint32 taskTimePot = 0;
    uint32 currUsage = 0;
    ((hcasSch)(rec->casSch))->time->iMeasure.start(&taskTimePot);
#endif

    for(i = 0; i < rec->task.taskGroupNum; i++){
        // 查看激活任务，并执行最高优先级任务
        taskMask = rec->task.actMask[i];
        if(taskMask != 0){
            curTask = (taskMask & (taskMask ^ (taskMask - 1)));
            //taskMask ^= curTask;
            //rec->task.actMask[i] ^= curTask; // 容易引发不可控结果
            rec->task.actMask[i] &= (~curTask);
            taskIndex = log_2n(curTask);

            // 判断是否为一次性任务，是则把任务掩码去除
            if(rec->task.prdTick[i][taskIndex] == 0){
                rec->task.taskMask[i] &= (~curTask);
            }

            // 检查任务执行是否有丢失
            if((rec->task.tick - rec->task.startTick[i][taskIndex]) >= rec->task.prdTick[i][taskIndex]){
                // 任务丢失则认为只丢失一个
                errcode.id = (void *)(rec->task.taskGroup[i][taskIndex]);
                errcode.cpnPartId = casSch_taskExecute_pi;
                errcode.errClassify = EC_EC_se;
                errcode.errRanking = EC_ER_serious;
                errcode.errCode = casSch_taskExecute_task_miss;
                ((hcasSch)(rec->casSch))->err(rec->casSch, &errcode);

                // 更新下一调度起始时间
                rec->task.startTick[i][taskIndex] += rec->task.prdTick[i][taskIndex];
            }else if((rec->task.tick - rec->task.startTick[i][taskIndex]) >= (rec->task.prdTick[i][taskIndex] >> 1)){
                errcode.id = (void *)(rec->task.taskGroup[i][taskIndex]);
                errcode.cpnPartId = casSch_taskExecute_pi;
                errcode.errClassify = EC_EC_se;
                errcode.errRanking = EC_ER_warning;
                errcode.errCode = casSch_taskExecute_task_delay;
                ((hcasSch)(rec->casSch))->err(rec->casSch, &errcode);
            }else{
                ;
            }

            // 执行任务
            rec->task.taskGroup[i][taskIndex]();

            break;
        }
    }

    // 返回查询任务激活状态
    rec->next = smcasSch_sta_update;

#if (CASSCH_TASK_MEASURE_ENABLE == 1)
    ((hcasSch)(rec->casSch))->taskTime = ((hcasSch)(rec->casSch))->time->iMeasure.end(taskTimePot);
    // 当前使用率需要用taskTime根据CASSCH_TIMER_PRD_CFG/CASSCH_TIME_MEASURE_PRECISION_CFG进行计算
    // 目前时间测量精确到0.1us，使用率精确到0.1%，比值关系需要满足1000倍关系，所以taskTime刚好满足
    //currUsage = ((hcasSch)(rec->casSch))->taskTime / ((CASSCH_TIMER_PRD_CFG / CASSCH_TIME_MEASURE_PRECISION_CFG) / 1000.0L));
    currUsage = ((hcasSch)(rec->casSch))->taskTime;
    ((hcasSch)(rec->casSch))->usage = lowpassFilter(currUsage, ((hcasSch)(rec->casSch))->usage, 3);
#endif
}

/*smcasSch_act_default
* 输入: hStaRec 状态记录结构体指针
* 输出: 无
***********************************************/
void smcasSch_act_default(void *hStaRec){
    hsmcasSchRec rec = (hsmcasSchRec)hStaRec;
    //((hcasSch)(rec->casSch))->
    errCode errcode;

    errcode.id = (void *)rec;
    errcode.cpnPartId = casSch_smcasSch_pi;
    errcode.errClassify = EC_EC_se;
    errcode.errRanking = EC_ER_serious;
    errcode.errCode = casSch_smcasSch_sta_default;
    ((hcasSch)(rec->casSch))->err(rec->casSch, &errcode);

    rec->next = smcasSch_sta_update;
}


/***********************************************************
* 组件定义
***********************************************************/
/*组件类初始化函数
* 输入: cthis casSch类指针
* 输出: hcasSch cthis/OOPC_NULL
***********************************************/
hcasSch casSch_init(hcasSch cthis, hstaAct smcasSch, hvfbOcasSch vfbOcasSch, hmeasure time){
    // 注入实例配置
    cthis->smcasSch = smcasSch;
    cthis->vfbOcasSch = vfbOcasSch;
    cthis->time = time;

    return cthis;
}

/*组件运行函数
* 输入: t casSch类指针
* 输出: 无
***********************************************/
void casSch_run(hcasSch t){
    SMRE(t->smcasSch, t->smcasSchRec);
}

/*casSch_tick 节拍更新
* 输入: t casSch类指针
* 输出: 无
***********************************************/
void casSch_tick(hcasSch t){
    t->smcasSchRec.task.tick++;
    t->tickOut(t);
}

/*casSch_tickOut 节拍输出
* 输入: t casSch类指针
* 输出: 无
***********************************************/
void casSch_tickOut(hcasSch t){
    t->vfbOcasSch->tickOut(t->vfbOcasSch);
}

/*casSch_err 错误输出
* 输入: t casSch类指针
* 输出: 无
***********************************************/
void casSch_err(hcasSch t, herrCode code){
    t->vfbOcasSch->err(t->vfbOcasSch, code);
}

/*casSch_addTask 添加任务
* 输入: t casSch类指针
* 输出: 无
***********************************************/
void casSch_addTask(hcasSch t, int16 id, void(*schTask)(void), uint16 prdTick, uint16 startTick){
    errCode errcode;
    uint32 taskMask = 0;
    uint32 curTask = 0;
    int16 taskGroup = 0;
    int16 taskIndex = 0;

    if(id > (t->smcasSchRec.task.taskGroupNum * 32)){
        errcode.id = (void *)t;
        errcode.cpnPartId = casSch_addTask_pi;
        errcode.errClassify = EC_EC_se;
        errcode.errRanking = EC_ER_warning;
        errcode.errCode = casSch_addTask_id_outOfRange;
        t->err(t, &errcode);
    }else{
        taskGroup = (id >> 5);
        taskIndex = (id & 0x001F);
        curTask = ((uint32)1 << taskIndex);
        taskMask = t->smcasSchRec.task.taskMask[taskGroup];

        // 判断任务是否存在
        if ((taskMask & curTask) != 0){
            errcode.id = (void *)t;
            errcode.cpnPartId = casSch_addTask_pi;
            errcode.errClassify = EC_EC_se;
            errcode.errRanking = EC_ER_warning;
            errcode.errCode = casSch_addTask_task_exist;
            t->err(t, &errcode);
        }else{
            t->smcasSchRec.task.taskMask[taskGroup] |= curTask;
            t->smcasSchRec.task.taskGroup[taskGroup][taskIndex] = schTask;
            t->smcasSchRec.task.prdTick[taskGroup][taskIndex] = prdTick;
            t->smcasSchRec.task.startTick[taskGroup][taskIndex] = startTick;
        }
    }
}

/*casSch_delTask 删除任务
* 输入: t casSch类指针
* 输出: 无
***********************************************/
void casSch_delTask(hcasSch t, int16 id, void(*schTask)(void)){
    errCode errcode;
    uint32 taskMask = 0;
    uint32 curTask = 0;
    int16 taskGroup = 0;
    int16 taskIndex = 0;

    if(id > (t->smcasSchRec.task.taskGroupNum * 32)){
        errcode.id = (void *)t;
        errcode.cpnPartId = casSch_delTask_pi;
        errcode.errClassify = EC_EC_se;
        errcode.errRanking = EC_ER_warning;
        errcode.errCode = casSch_delTask_id_outOfRange;
        t->err(t, &errcode);
    }else{
        taskGroup = (id >> 5);
        taskIndex = (id & 0x001F);
        curTask = ((uint32)1 << taskIndex);
        taskMask = t->smcasSchRec.task.taskMask[taskGroup];

        // 判断任务是否存在
        if((taskMask & curTask) == 0){
            errcode.id = (void *)t;
            errcode.cpnPartId = casSch_delTask_pi;
            errcode.errClassify = EC_EC_se;
            errcode.errRanking = EC_ER_warning;
            errcode.errCode = casSch_delTask_task_null;
            t->err(t, &errcode);
        }else{
            // 判断是否为目标任务
            if(t->smcasSchRec.task.taskGroup[taskGroup][taskIndex] != schTask){
                errcode.id = (void *)t;
                errcode.cpnPartId = casSch_delTask_pi;
                errcode.errClassify = EC_EC_se;
                errcode.errRanking = EC_ER_warning;
                errcode.errCode = casSch_delTask_task_false;
                t->err(t, &errcode);
            }else{
                t->smcasSchRec.task.actMask[taskGroup] &= (~curTask);
                t->smcasSchRec.task.taskMask[taskGroup] &= (~curTask);
                t->smcasSchRec.task.taskGroup[taskGroup][taskIndex] = schTaskDefault;
                t->smcasSchRec.task.prdTick[taskGroup][taskIndex] = 0;
                t->smcasSchRec.task.startTick[taskGroup][taskIndex] = 0;
            }
        }
    }
}

/*组件类构造函数
* 输入: cthis casSch类指针
* 输出: hcasSch cthis/OOPC_NULL
***********************************************/
CC(casSch){
    int16 i = 0;
    int16 j = 0;

    // 功能函数配置
    cthis->init = casSch_init;
    cthis->run = casSch_run;
    cthis->tick = casSch_tick;
    cthis->tickOut = casSch_tickOut;
    cthis->err = casSch_err;
    cthis->addTask = casSch_addTask;
    cthis->delTask = casSch_delTask;

    // 参数配置
    cthis->usage = 0;
    cthis->taskTime = 0;

    cthis->smcasSchRec.next = smcasSch_sta_init;
    cthis->smcasSchRec.task.tick = 0;
    cthis->smcasSchRec.task.taskGroupNum = SCH_TASK_GROUP_NUM;
    for(i = 0; i < cthis->smcasSchRec.task.taskGroupNum; i++){
        cthis->smcasSchRec.task.actMask[i] = 0;
        cthis->smcasSchRec.task.taskMask[i] = 0;

        for(j = 0; j < 32; j++){
            cthis->smcasSchRec.task.startTick[i][j] = 0;
            cthis->smcasSchRec.task.prdTick[i][j] = 0;
            cthis->smcasSchRec.task.taskGroup[i][j] = schTaskDefault;
        }
    }

    return cthis;
}
/*组件类析构函数
* 输入: cthis casSch类指针
* 输出: OOPC_RETURN_DATATYPE OOPC_TRUE/OOPC_FALSE
***********************************************/
CD(casSch){
    return OOPC_TRUE;
}


/***********************************************************
* 组件异步调度功能函数
***********************************************************/
/*异步调度功能函数
***********************************************/
void casSch_abi_timer(void)
{
    casSchA.tick(casSchA.self);
}
void casSch_abi_mainLoop(void)
{
    casSchA.run(casSchA.self);
}


/***********************************************************
* 组件实例化
***********************************************************/
/*组件类实例
***********************************************/
casSch casSchA;


/**************************** Copyright(C) pxf ****************************/
