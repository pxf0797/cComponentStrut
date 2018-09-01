/*************************************************
 * Copyright © person
 * File name    : sm.h
 * Author       : pxf
 * Version      : v1.0
 * Created on   : 2018/3/10
 * Description  : 本文件为方便状态机创建提供一系列宏；
 *                1.状态机创建第一步必须定义好状态集合sta_list，基本init,default两状态默认会给出的;
 *                2.状态机创建第二步使用宏SMDC声明状态机运行过程中状态记录结构体StaRec，基本sta next参数必不可少；
 *                3.状态机创建第三步定义状态机，使用宏SMDF；
 *                4.状态机创建第四步为各状态分别建立状态动作void sm_type##_##_act_##sm_sta(void *hStaRec)；
 *                5.状态机创建第五步使用宏SMR为状态机给入时钟对状态机进行驱动；
 * Others       : 无
 * History      : 180310 pxf 初次建立
 *                180819 pxf 1.增加状态机指针hstaAct/hhstaAct；
 *                           2.增加状态机指针运行宏SMRE
 ************************************************/

#ifndef SM_H_
#define SM_H_

// 版本定义---------------------------------------------------------------------
#define SM_VERSION    0xC01D01          // C代表v，D代表.，版本v1.01

// 基本类型定义
typedef unsigned char sta;
typedef void (*staAct)(void *hStaRec);  // state action
typedef staAct *hstaAct, **hhstaAct;    // 状态机指针

// 状态及状态输出
#define SD(sm_type, sm_sta) sm_type##_sta_##sm_sta,                       // state define 注意后有","，各状态定义
#define SADC(sm_type, sm_sta) void sm_type##_act_##sm_sta(void *hStaRec); // state action declaration 注意后有";"，各状态动作输出声明
#define SADF(sm_type, sm_sta) sm_type##_act_##sm_sta,                     // state action define 注意后有","，各状态动作输出定义

// 状态机的状态类型进行罗列
// 其中init,default这两个状态在状态机声明时默认会给出，所以在这里状态罗列时就不必要罗列出来了
/*
#define STA_LIST(_)          \
    _(sm_type, count)        \
    _(sm_type, done)
    */

// 使用X_MACRO
// state machine declaration 状态机声明
// 需要声明状态机状态动作的状态记录结构体
// 其中next为必填参数，作为状态机运行时对应的下一动作
/*
    typedef struct StaRec   // 对状态机参数封装state record
    {
        sta next;    // 必选项且必须放在第一个，作为状态机的下一次动作
        //sta last;  // 根据需要，是否输入的上一次状态
        ...          // 根据需要，是否输入一些其他参数
    } *hStaRec, StaRec;
    */
#define SMDC(sm_type, sta_list)                                 \
typedef struct sm_type##Rec *h##sm_type##Rec, sm_type##Rec;     \
enum sm_type##_stas{                                            \
    sm_type##_sta_init = 0,                                     \
    sta_list(SD)                                                \
    sm_type##_sta_default                                       \
};                                                              \
void sm_type##_act_init(void *hStaRec);                         \
sta_list(SADC)                                                  \
void sm_type##_act_default(void *hStaRec);                      \
extern staAct sm_type[sm_type##_sta_default + 1];               \
struct sm_type##Rec
// state machine define 状态机定义
#define SMDF(sm_type, sta_list)                                 \
staAct sm_type[sm_type##_sta_default + 1] = {                   \
    sm_type##_act_init,                                         \
    sta_list(SADF)                                              \
    sm_type##_act_default                                       \
}
// state machine run 状态驱动，相对来说就是给时钟周期
//static StaRec StaRunRec = {sm_type##_sta_init}; // 必须定义初始状态
#define SMR(sm_type)                                            \
do{                                                             \
    static sm_type##Rec sm_type##RunRec = {sm_type##_sta_init}; \
    sm_type[sm_type##RunRec.next](&sm_type##RunRec);            \
}while(0)
// state machine run entity 使用状态机指针运行
// 当前是在有状态机指针定义情况下，不使用SMR运行状态机
#define SMRE(sm_entity_ptr, sm_rec)  (sm_entity_ptr)[(sm_rec).next](&(sm_rec))

#endif /* SM_H_ */

/**************************** Copyright(C) pxf ****************************/
