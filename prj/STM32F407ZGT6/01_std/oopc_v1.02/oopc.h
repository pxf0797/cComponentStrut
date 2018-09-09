/*************************************************
 * Copyright © person
 * File name    : oopc.h
 * Author       : pxf
 * Version      : v1.0
 * Created on   : 2018/2/8
 * Description  : 本文件内定义的宏用于生成C代码的面向对象。
 *                1.目前面向对象的接口、抽象类、实类之间的基本关系操作都已实现；
 *                2.INF/AC/CL分别用于声明接口、抽象类、实类，其使用尽量放在.h文件中；
 *                3.ACC/ACD/CC/CD分别用于定义抽象类、实类构造及析构函数，其使用必须在.c文件中；
 *                4.CACC/CACD/CCC/CCD分别用于实类实例化时构造函数中调用被继承类（抽象类、实类）
 *                  的构造及析构函数来实例化被继承类，其使用必须在.c文件中；
 *                5.IMPL/EXT分别用于继承接口及抽象类、实类；
 *                6.INJ实类可注入一个类多个实例；
 *                7.SUB/SUBC分别用于在接口及抽象类、实类中的函数内获得继承子类指针cthis；
 *                8.CN/CNNP/CF实例化或释放实类对象；
 *                9.由于CN/CNNP/CF/CCC操作后没有返回值，可以通过OPRS查看前一步操作结果；
 *                10.实类声明中必须附带两个参数self,init；
 *                   self - 指向自身的指针，也可以指示当前实例是否可用，self指向自身时实类可用，self为OOPC_NULL时实类已释放；
 *                   init - 配置实类中参数，init函数有个要求在函数参数声明中指向自身实类指针必须声明为cthis；
 *                          为了初始化更加统一，接口及抽象类需要通过init传递进行配置，
 *                          实类自身函数需要通过FS进行设置，除非特别需求可通过init配置；
 *                          实类如有继承，则被继承类所有相关函数都得通过init进行配置；
 * Others       : 无
 * History      : 180208 pxf 初次建立
 *                180302 pxf 1.为适应不同编译器对实类进行的实例化，增加特殊的无参宏CNNP
 *                           2.增加宏版本定义，当前版本为v1.01
 *                180816 pxf 1.因使用频率特别低，使用代码直接替代更加方便，删除宏FS
 *                           2.增加依赖注入宏INJ，使得实类可注入一个类多个实例
 *                           3.CN/CCC增加在传递不可变参数时，使用宏定义参数进行传递
 *                           4.版本升级v1.02
 ************************************************/

#ifndef OOPC_H_
#define OOPC_H_

// >>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>
// 版本定义---------------------------------------------------------------------
#define OOPC_MACRO_VERSION              0xC01D02    // C代表v，D代表.，版本v1.02

// 通用宏定义-------------------------------------------------------------------
#define OOPC_FALSE                      0           // （操作）失败
#define OOPC_TRUE                       1           // （操作）成功
#define OOPC_NULL                       ((void *)0) // 空指针

// 配置选项---------------------------------------------------------------------
#define OOPC_USE_USER_DEFINED_OFFSETOF  OOPC_TRUE   // 是否使用用户定义的OOPC_OFFSETOF，OOPC_FALSE时使用C标准库中的offsetof
#define OOPC_USE_STATIC_INLINE_OPTIMIZE OOPC_TRUE   // 是否使用static inline对构造及析构函数代码调用进行优化
#define OOPC_CN_CCC_SUPPORT_FLEXIABLE_PARAM OOPC_TRUE // 是否支持可变参数对类进行实例化
#define OOPC_RETURN_DATATYPE            int         // 定义析构函数等返回数据类型

// 配置选择---------------------------------------------------------------------
#if (OOPC_USE_USER_DEFINED_OFFSETOF == OOPC_TRUE)   // 配置OOPC_OFFSETOF
    // 有些环境可能不支持，不过，这种情形极少出现
    #define OOPC_OFFSETOF(type, member) (size_t)&(((type *)0)->member)
#else
    #include <stddef.h>
	// size_t offsetof(structName, memberName);
	// 第一个参数是结构体的名字，第二个参数是结构体成员的名字。
	// 该宏返回结构体structName中成员memberName的偏移量。偏移量是size_t类型的。
    #define OOPC_OFFSETOF               offsetof
#endif
#if (OOPC_USE_STATIC_INLINE_OPTIMIZE == OOPC_TRUE)  // 配置OOPC_STATIC_INLINE
	#define OOPC_STATIC_INLINE          static inline
#else
	#define OOPC_STATIC_INLINE
#endif
// >>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>

// >>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>
// 接口及类的继承关系-----------------------------------------------------------
#define IMPL(type)                      type type   // 接口、抽象类进行继承Implement
#define EXT(type)                       h##type type// 实类进行继承Extends
#define INJ(type, obj)                  h##type obj // 实类进行依赖注入Injection
                                                    // 与实类进行继承有相似性，依赖注入可以注入多个相同的类实例，并且名称可自定

// 类的继承建议一级继承，不建议多级继承------------------------------------------
// 实类继承子类（继承类）指针 subordinate,self pointer
#define SUBC(selfpointer, hselftype, childtype)                      \
h##childtype cthis = ((h##childtype)((char *)(*selfpointer) - OOPC_OFFSETOF(childtype, hselftype)))
// 抽象类或接口继承子类（继承类）指针
#define SUB(selfpointer, selftype, childtype)                        \
h##childtype cthis = ((h##childtype)((char *)selfpointer - OOPC_OFFSETOF(childtype, selftype)))
// >>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>

// >>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>
// 接口及抽象类、实类的声明------------------------------------------------------
// Interface接口进行声明
#define INF(type)                                                    \
typedef struct type *h##type, type;                                  \
struct type
// Abstract Class抽象类进行声明
#define AC(type)                                                     \
typedef struct type *h##type, type;                                  \
struct type
// Class实类进行声明
// 实类声明中必须要以下self,init两个有参数定义
// self指向自身，最好放在参数的第一个，h##type self
// init有参数要求并且返回自身类型指针，h##type (*init)(classptr cthis,...)
// init参数中类指针必须声明为cthis，而其他所有函数参数中都不可以有cthis的参数出现
// 接口函数、抽象类函数、以及类自身不在同一文件内的函数可以通过init函数传参进行初始化
// 类其余在同一文件内函数最好通过FS直接进行配置
// 示例：
// CL(Aaa)
// {
//	   hAaa self;
//	   hAaa (*init)(hAaa cthis, ...);
//	   ...
// }
#define CL(type)                                                     \
typedef struct type **hh##type, *h##type, type;                      \
h##type type##_new(void *self);                                      \
OOPC_RETURN_DATATYPE type##_delete(h##type t);                       \
struct type
// >>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>

// >>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>
// 抽象类、实类构造函数及析构函数定义--------------------------------------------
// 定义抽象类构造函数abstract class constructor，需要返回值cthis/OOPC_NULL
#define ACC(type)                                                    \
OOPC_STATIC_INLINE h##type type##_ctor(h##type cthis);               \
OOPC_STATIC_INLINE h##type type##_ctor(h##type cthis)
// 定义抽象类析构函数abstract class destructor，需要返回值OOPC_TRUE/OOPC_FALSE
#define ACD(type)                                                    \
OOPC_STATIC_INLINE OOPC_RETURN_DATATYPE type##_dtor(h##type cthis);  \
OOPC_STATIC_INLINE OOPC_RETURN_DATATYPE type##_dtor(h##type cthis)
// 定义实类构造函数class constructor，需要返回值cthis/OOPC_NULL
#define CC(type)                                                     \
OOPC_STATIC_INLINE h##type type##_ctor(h##type cthis);               \
h##type type##_new(void *self){                                      \
    h##type cthis = (h##type)self;                                   \
    h##type Rtv = OOPC_NULL;                                         \
    if(OOPC_NULL != cthis){                                          \
        cthis->self = cthis;                                         \
        if(OOPC_NULL == type##_ctor(cthis)){                         \
            cthis->self = OOPC_NULL;                                 \
            Rtv = OOPC_NULL;                                         \
        }else{                                                       \
            Rtv = cthis;                                             \
        }                                                            \
    }else{                                                           \
    	Rtv = OOPC_NULL;                                             \
    }                                                                \
    return Rtv;                                                      \
    /* 当前不去获取内存，只对传输进来的内存进行配置 */               \
}                                                                    \
OOPC_STATIC_INLINE h##type type##_ctor(h##type cthis)
// 定义实类析构函数class destructor，需要返回值OOPC_TRUE/OOPC_FALSE
#define CD(type)                                                     \
OOPC_STATIC_INLINE OOPC_RETURN_DATATYPE type##_dtor(h##type cthis);  \
OOPC_RETURN_DATATYPE type##_delete(h##type cthis){                   \
	OOPC_RETURN_DATATYPE Rtv = OOPC_FALSE;                           \
	if(OOPC_NULL != cthis){                                          \
		cthis->self = OOPC_NULL;                                     \
	    if(OOPC_TRUE == type##_dtor(cthis)){                         \
            Rtv = OOPC_TRUE;                                         \
        }else{                                                       \
            Rtv = OOPC_FALSE;                                        \
        }                                                            \
	}else{                                                           \
		Rtv = OOPC_FALSE;                                            \
	}                                                                \
	return Rtv;                                                      \
	/* 当前不去释放内存，只对传输进来的内存进行配置 */               \
}                                                                    \
OOPC_STATIC_INLINE OOPC_RETURN_DATATYPE type##_dtor(h##type cthis)
// >>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>

// >>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>
// 类实例化时，抽象类、实类父类构造及析构函数的调用-------------------------------
// 调用抽象类构造函数call abstract class constructor，有返回值cthis/OOPC_NULL
#define CACC(father)                    father##_ctor(&(cthis->father))
// 调用抽象类析构函数call abstract class destructor，有返回值OOPC_TRUE/OOPC_FALSE
#define CACD(father)                    father##_dtor(&(cthis->father))
// 调用类构造函数call class constructor，有返回值cthis/OOPC_NULL
#if (OOPC_CN_CCC_SUPPORT_FLEXIABLE_PARAM == OOPC_TRUE)
#define CCC(father, fatherptr, ...)                                  \
do{                                                                  \
    cthis->father = father##_new((void *)(fatherptr));               \
    if(OOPC_NULL != cthis->father){                                  \
        if(OOPC_NULL == cthis->father->init(cthis->father, __VA_ARGS__)){ \
        	if(OOPC_TRUE == father##_delete(cthis->father)){         \
        		;                                                    \
        	}else{                                                   \
        		;                                                    \
        	}                                                        \
        	cthis->father = OOPC_NULL;                               \
        }else{                                                       \
        	;                                                        \
        }                                                            \
    }else{                                                           \
    	;                                                            \
    }                                                                \
}while(0)
#else
//#define ccc_param  param1,param2...
#define CCC(father, fatherptr, param)                                \
do{                                                                  \
    cthis->father = father##_new((void *)(fatherptr));               \
    if(OOPC_NULL != cthis->father){                                  \
        if(OOPC_NULL == cthis->father->init(cthis->father, param)){  \
            if(OOPC_TRUE == father##_delete(cthis->father)){         \
                ;                                                    \
            }else{                                                   \
                ;                                                    \
            }                                                        \
            cthis->father = OOPC_NULL;                               \
        }else{                                                       \
            ;                                                        \
        }                                                            \
    }else{                                                           \
        ;                                                            \
    }                                                                \
}while(0)
#endif
// 调用类析构函数call class destructor，有返回值OOPC_TRUE/OOPC_FALSE
#define CCD(father)                     father##_delete((cthis->father))
// >>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>

// >>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>
// 实类实例化及释放Class New/Free，参数个数任意----------------------------------
// CF多个参数是类实例化通过init函数进行配置的参数传递决定的
#if (OOPC_CN_CCC_SUPPORT_FLEXIABLE_PARAM == OOPC_TRUE)
#define CN(type, classptr, ...)                                      \
do{                                                                  \
    if(OOPC_NULL != type##_new((void *)(classptr))){                 \
		if(OOPC_NULL == (classptr)->init((classptr), __VA_ARGS__)){  \
        	if(OOPC_TRUE == type##_delete(classptr)){                \
        		;                                                    \
        	}else{                                                   \
        		;                                                    \
        	}                                                        \
        }else{                                                       \
        	;                                                        \
        }                                                            \
    }else{                                                           \
        ;                                                            \
    }                                                                \
}while(0)
#else
//#define cn_param  param1,param2...
#define CN(type, classptr, param)                                    \
do{                                                                  \
    if(OOPC_NULL != type##_new((void *)(classptr))){                 \
        if(OOPC_NULL == (classptr)->init((classptr), param)){        \
            if(OOPC_TRUE == type##_delete(classptr)){                \
                ;                                                    \
            }else{                                                   \
                ;                                                    \
            }                                                        \
        }else{                                                       \
            ;                                                        \
        }                                                            \
    }else{                                                           \
        ;                                                            \
    }                                                                \
}while(0)
#endif
// Class New Without(No) Param无参类实例化
#define CNNP(type, classptr)                                         \
do{                                                                  \
    if(OOPC_NULL != type##_new((void *)(classptr))){                 \
		if(OOPC_NULL == (classptr)->init(classptr)){                 \
        	if(OOPC_TRUE == type##_delete(classptr)){                \
        		;                                                    \
        	}else{                                                   \
        		;                                                    \
        	}                                                        \
        }else{                                                       \
        	;                                                        \
        }                                                            \
    }else{                                                           \
        ;                                                            \
    }                                                                \
}while(0)
// ClassFree对类资源进行释放
#define CF(type, classptr)                                           \
do{                                                                  \
	if(OOPC_NULL != (classptr)){                                     \
		if(OOPC_TRUE == type##_delete(classptr)){                    \
            ;                                                        \
        }else{                                                       \
        	;                                                        \
        }                                                            \
	}else{                                                           \
		;                                                            \
	}                                                                \
}while(0)
// 由于CN/CNNP/CF/CCC调用后没有返回值，通过以下宏查看操作结果operation result，self/OOPC_NULL
#define OPRS(class)                     (class).self
// >>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>

#endif /* OOPC_H_ */

/**************************** Copyright(C) pxf ****************************/
