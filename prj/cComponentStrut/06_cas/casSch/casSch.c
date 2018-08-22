/*
 * casSch.c
 *
 *  Created on: 2018年8月17日
 *      Author: pxf
 */

#include "casSch.h"
#include "..\..\04_abi\abi.h"
#include "..\..\11_vfbM\casSch\vfbMcasSch.h"
#include "..\..\02_bm\func\func.h"

// --------------------------------------------------------------
// 组件初始化
// --------------------------------------------------------------
// 组件初始化------------------------
int16 casSchInit(void)
{
    int16 rtv = 0;

    CN(casSch, &casSchA, &time, &vfbOcasSchA, &schSm[0]);
    if (OPRS(casSchA) != OOPC_NULL)
    {
        rtv = vfbOcasSchInit();
    }
    else
    {
        rtv = -1;
    }

    return rtv;
}

// --------------------------------------------------------------
// 组件调度
// --------------------------------------------------------------
// 组件进行调度--------------------------


// --------------------------------------------------------------
// 通用功能函数
// --------------------------------------------------------------
// 默认任务
static void schTaskDefault(void)
{}

// 纯粹求2^n的对应的对数n
static inline int16 log_2n(uint32 num)
{
    int16 n = 0;
    if ((num & 0xFFFF0000U) != 0U)
    {
        n += 16;
    }
    if ((num & 0xFF00FF00U) != 0U)
    {
        n += 8;
    }
    if ((num & 0xF0F0F0F0U) != 0U)
    {
        n += 4;
    }
    if ((num & 0xCCCCCCCCU) != 0U)
    {
        n += 2;
    }
    if ((num & 0xAAAAAAAAU) != 0U)
    {
        n += 1;
    }

    return n;
}


// --------------------------------------------------------------
// 调度器管理状态机
// --------------------------------------------------------------
SMDF(schSm, SCH_SM_STA_LIST);

void schSm_act_init(void *hStaRec)
{
    hschSmRec rec = (hschSmRec)hStaRec;

    rec->casSch = (void *)&casSchA;

    rec->next = schSm_sta_update;
}
void schSm_act_update(void *hStaRec)
{
    hschSmRec rec = (hschSmRec)hStaRec;
    uint32 taskMask = 0;
    uint32 curTask = 0;
    int16 taskIndex = 0;
    int16 i = 0;

    for (i = 0; i < rec->task.taskGroupNum; i++)
    {
        // 更新各组激活任务
        taskMask = rec->task.taskMask[i];
        while (taskMask != 0)
        {
            curTask = (taskMask & (taskMask ^ (taskMask - 1)));
            taskMask ^= curTask;
            taskIndex = log_2n(curTask);

            if ((rec->task.tick - rec->task.startTick[i][taskIndex]) >= rec->task.prdTick[i][taskIndex])
            {
                // 更新激活状态以及下一激活节拍
                rec->task.actMask[i] |= curTask;
                rec->task.startTick[i][taskIndex] += rec->task.prdTick[i][taskIndex];
            }
        }
    }

    // 所有任务更新后进入执行状态查看是否有要执行任务
    rec->next = schSm_sta_execute;
}
void schSm_act_execute(void *hStaRec)
{
    hschSmRec rec = (hschSmRec)hStaRec;
    uint32 taskMask = 0;
    uint32 curTask = 0;
    int16 taskIndex = 0;
    int16 i = 0;
    errCode errcode;
#if (CASSCH_TASK_MEASURE_ENABLE == 1)
    static uint32 taskTimePot = 0;
    uint32 currUsage = 0;
    ((hcasSch)rec->casSch)->time->iMeasure.start(&taskTimePot);
#endif

    for (i = 0; i < rec->task.taskGroupNum; i++)
    {
        // 查看激活任务，并执行最高优先级任务
        taskMask = rec->task.actMask[i];
        if (taskMask != 0)
        {
            curTask = (taskMask & (taskMask ^ (taskMask - 1)));
            //taskMask ^= curTask;
            //rec->task.actMask[i] ^= curTask; // 容易引发不可控结果
            rec->task.actMask[i] &= (~curTask);
            taskIndex = log_2n(curTask);

            // 判断是否为一次性任务，是则把任务掩码去除
            if (rec->task.prdTick[i][taskIndex] == 0)
            {
                rec->task.taskMask[i] &= (~curTask);
            }

            // 检查任务执行是否有丢失
            if ((rec->task.tick - rec->task.startTick[i][taskIndex]) >= rec->task.prdTick[i][taskIndex])
            {
                // 任务丢失则认为只丢失一个
                errcode.id = (void *)(rec->task.taskGroup[i][taskIndex]);
                errcode.cpnPartId = casSch_taskExecute_pi;
                errcode.errClassify = EC_EC_se;
                errcode.errRanking = EC_ER_serious;
                errcode.errCode = casSch_taskExecute_task_miss;
                ((hcasSch)rec->casSch)->err(rec->casSch, &errcode);

                // 更新下一调度起始时间
                rec->task.startTick[i][taskIndex] += rec->task.prdTick[i][taskIndex];
            }
            else if ((rec->task.tick - rec->task.startTick[i][taskIndex]) >= (rec->task.prdTick[i][taskIndex] >> 1))
            {
                errcode.id = (void *)(rec->task.taskGroup[i][taskIndex]);
                errcode.cpnPartId = casSch_taskExecute_pi;
                errcode.errClassify = EC_EC_se;
                errcode.errRanking = EC_ER_warning;
                errcode.errCode = casSch_taskExecute_task_delay;
                ((hcasSch)rec->casSch)->err(rec->casSch, &errcode);
            }
            else
            {
                ;
            }

            // 执行任务
            rec->task.taskGroup[i][taskIndex]();

            break;
        }
    }

    // 返回查询任务激活状态
    rec->next = schSm_sta_update;

#if (CASSCH_TASK_MEASURE_ENABLE == 1)
    ((hcasSch)rec->casSch)->taskTime = ((hcasSch)rec->casSch)->time->iMeasure.end(taskTimePot);
    // 当前使用率需要用taskTime根据CASSCH_TIMER_PRD_CFG/CASSCH_TIME_MEASURE_PRECISION_CFG进行计算
    // 目前时间测量精确到0.1us，使用率精确到0.1%，比值关系需要满足1000倍关系，所以taskTime刚好满足
    //currUsage = (((hcasSch)rec->casSch)->taskTime / ((CASSCH_TIMER_PRD_CFG / CASSCH_TIME_MEASURE_PRECISION_CFG) / 1000.0L));
    currUsage = ((hcasSch)rec->casSch)->taskTime;
    ((hcasSch)rec->casSch)->usage = lowpassFilter(currUsage, ((hcasSch)rec->casSch)->usage, 3);
#endif
}
void schSm_act_default(void *hStaRec)
{
    hschSmRec rec = (hschSmRec)hStaRec;
    errCode errcode;

    errcode.id = (void *)rec;
    errcode.cpnPartId = casSch_schSm_pi;
    errcode.errClassify = EC_EC_se;
    errcode.errRanking = EC_ER_serious;
    errcode.errCode = casSch_schSm_sta_default;
    ((hcasSch)rec->casSch)->err(rec->casSch, &errcode);

    rec->next = schSm_sta_update;
}


// --------------------------------------------------------------
// 调度任务组件类定义
// --------------------------------------------------------------
hcasSch casSch_init(hcasSch cthis, hmeasure time, hvfbOcasSch vfbOcasSch, hstaAct schSm)
{
    cthis->time = time;
    cthis->vfbOcasSch = vfbOcasSch;
    cthis->schSm = schSm;

    return cthis;
}

void casSch_timer(hcasSch t)
{
    t->schSmRec.task.tick++;
    t->tickOut(t);
}
void casSch_run(hcasSch t)
{
    SMRE(t->schSm, t->schSmRec);
}

void casSch_tickOut(hcasSch t)
{
    t->vfbOcasSch->tickOut(t->vfbOcasSch);
}
void casSch_err(hcasSch t, herrCode code)
{
    t->vfbOcasSch->err(t->vfbOcasSch, code);
}

void casSch_addTask(hcasSch t, int16 id, void(*schTask)(void), uint16 prdTick, uint16 startTick)
{
    errCode errcode;
    uint32 taskMask = 0;
    uint32 curTask = 0;
    int16 taskGroup = 0;
    int16 taskIndex = 0;

    if (id > (t->schSmRec.task.taskGroupNum * 32))
    {
        errcode.id = (void *)t;
        errcode.cpnPartId = casSch_addTask_pi;
        errcode.errClassify = EC_EC_se;
        errcode.errRanking = EC_ER_warning;
        errcode.errCode = casSch_addTask_id_outOfRange;
        t->err(t, &errcode);
    }
    else
    {
        taskGroup = (id >> 5);
        taskIndex = (id & 0x001F);
        curTask = ((uint32)1 << taskIndex);
        taskMask = t->schSmRec.task.taskMask[taskGroup];

        // 判断任务是否存在
        if ((taskMask & curTask) != 0)
        {
            errcode.id = (void *)t;
            errcode.cpnPartId = casSch_addTask_pi;
            errcode.errClassify = EC_EC_se;
            errcode.errRanking = EC_ER_warning;
            errcode.errCode = casSch_addTask_task_exist;
            t->err(t, &errcode);
        }
        else
        {
            t->schSmRec.task.taskMask[taskGroup] |= curTask;
            t->schSmRec.task.taskGroup[taskGroup][taskIndex] = schTask;
            t->schSmRec.task.prdTick[taskGroup][taskIndex] = prdTick;
            t->schSmRec.task.startTick[taskGroup][taskIndex] = startTick;
        }
    }
}
void casSch_delTask(hcasSch t, int16 id, void(*schTask)(void))
{
    errCode errcode;
    uint32 taskMask = 0;
    uint32 curTask = 0;
    int16 taskGroup = 0;
    int16 taskIndex = 0;

    if (id > (t->schSmRec.task.taskGroupNum * 32))
    {
        errcode.id = (void *)t;
        errcode.cpnPartId = casSch_delTask_pi;
        errcode.errClassify = EC_EC_se;
        errcode.errRanking = EC_ER_warning;
        errcode.errCode = casSch_delTask_id_outOfRange;
        t->err(t, &errcode);
    }
    else
    {
        taskGroup = (id >> 5);
        taskIndex = (id & 0x001F);
        curTask = ((uint32)1 << taskIndex);
        taskMask = t->schSmRec.task.taskMask[taskGroup];

        // 判断任务是否存在
        if ((taskMask & curTask) == 0)
        {
            errcode.id = (void *)t;
            errcode.cpnPartId = casSch_delTask_pi;
            errcode.errClassify = EC_EC_se;
            errcode.errRanking = EC_ER_warning;
            errcode.errCode = casSch_delTask_task_null;
            t->err(t, &errcode);
        }
        else
        {
            // 判断是否为目标任务
            if (t->schSmRec.task.taskGroup[taskGroup][taskIndex] != schTask)
            {
                errcode.id = (void *)t;
                errcode.cpnPartId = casSch_delTask_pi;
                errcode.errClassify = EC_EC_se;
                errcode.errRanking = EC_ER_warning;
                errcode.errCode = casSch_delTask_task_false;
                t->err(t, &errcode);
            }
            else
            {
                t->schSmRec.task.actMask[taskGroup] &= (~curTask);
                t->schSmRec.task.taskMask[taskGroup] &= (~curTask);
                t->schSmRec.task.taskGroup[taskGroup][taskIndex] = schTaskDefault;
                t->schSmRec.task.prdTick[taskGroup][taskIndex] = 0;
                t->schSmRec.task.startTick[taskGroup][taskIndex] = 0;
            }
        }
    }
}

CC(casSch)
{
    int16 i = 0;
    int16 j = 0;

    cthis->init = casSch_init;
    cthis->timer = casSch_timer;
    cthis->run = casSch_run;
    cthis->tickOut = casSch_tickOut;
    cthis->err = casSch_err;
    cthis->addTask = casSch_addTask;
    cthis->delTask = casSch_delTask;

    cthis->usage = 0;
    cthis->taskTime = 0;

    cthis->schSmRec.next = schSm_sta_init;
    cthis->schSmRec.task.tick = 0;
    cthis->schSmRec.task.taskGroupNum = SCH_TASK_GROUP_NUM;
    for (i = 0; i < cthis->schSmRec.task.taskGroupNum; i++)
    {
        cthis->schSmRec.task.actMask[i] = 0;
        cthis->schSmRec.task.taskMask[i] = 0;

        for (j = 0; j < 32; j++)
        {
            cthis->schSmRec.task.startTick[i][j] = 0;
            cthis->schSmRec.task.prdTick[i][j] = 0;
            cthis->schSmRec.task.taskGroup[i][j] = schTaskDefault;
        }
    }

    return cthis;
}
CD(casSch)
{
    return OOPC_TRUE;
}

// --------------------------------------------------------------
// 异步调度功能函数
// --------------------------------------------------------------
void casSch_abi_timer(void)
{
    casSchA.timer(casSchA.self);
}
void casSch_abi_mainLoop(void)
{
    casSchA.run(casSchA.self);
}


// --------------------------------------------------------------
// 组件类实例化
// --------------------------------------------------------------
casSch casSchA;

