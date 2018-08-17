/*
 * casSch.c
 *
 *  Created on: 2018Äê8ÔÂ17ÈÕ
 *      Author: pxf
 */

#include "casSch.h"


void schSm_act_init(void *hStaRec)
{}
void schSm_act_update(void *hStaRec)
{}
void schSm_act_execute(void *hStaRec)
{}
void schSm_act_default(void *hStaRec)
{}


hvfbOcasSch vfbOcasSch_init(hvfbOcasSch cthis,
        void (*tickOut)(hvfbOcasSch t),
        void (*err)(hvfbOcasSch t, herrCode code))
{
    cthis->tickOut = tickOut;
    cthis->err = err;

    return cthis;
}


CC(vfbOcasSch)
{
    cthis->init = vfbOcasSch_init;

    return cthis;
}

CD(vfbOcasSch)
{
    return OOPC_TRUE;
}



hcasSch casSch_init(hcasSch cthis, hmeasure time)
{
    cthis->time = time;

    return cthis;
}

void casSch_timer(hcasSch t)
{
    t->tick++;
}

void casSch_run(hcasSch t)
{
    ;
}

void casSch_tickOut(hcasSch t)
{
    ;
}
void casSch_err(hcasSch t, herrCode code)
{
    ;
}

void casSch_addTask(hcasSch t, int16 id, void(*schTask)(void))
{
    ;
}

void casSch_delTask(hcasSch t, int16 id, void(*schTask)(void))
{
    ;
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

    cthis->tick = 0;
    cthis->task.taskGroupNum = SCH_TASK_GROUP_NUM;
    for (i = 0; i < cthis->task.taskGroupNum; i++)
    {
        cthis->task.actTick[i] = 0;
        cthis->task.prdTick[i] = 0;
        cthis->task.actMask[i] = 0;
        cthis->task.taskMask[i] = 0;
        for (j = 0; j < 32; j++)
        {
            cthis->task.taskGroup[i][j] = 0;
        }
    }
    cthis->schSmRec.next = schSm_sta_init;

    return cthis;
}


void casSch_timer_bsp(void)
{}
void casSch_mainLoop_bsp(void)
{}




hvfbIcasSch vfbIcasSch_init(hvfbIcasSch cthis)
{
    return cthis;
}
void vfbIcasSch_addTask(hvfbIcasSch t, int16 id, void(*schTask)(void))
{
    t->casSch->addTask(t->casSch, id, schTask);
}
void vfbIcasSch_delTask(hvfbIcasSch t, int16 id, void(*schTask)(void))
{
    t->casSch->delTask(t->casSch, id, schTask);
}

CC(vfbIcasSch)
{
    cthis->init = vfbIcasSch_init;
    cthis->addTask = vfbIcasSch_addTask;
    cthis->delTask = vfbIcasSch_delTask;

    return cthis;
}

CD(vfbIcasSch)
{
    return OOPC_TRUE;
}










