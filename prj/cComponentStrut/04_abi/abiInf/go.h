/*
 * go.h
 *
 *  Created on: 2018Äê8ÔÂ17ÈÕ
 *      Author: pxf
 */

#ifndef GO_H_
#define GO_H_

CL(go)
{
    hgo self;
    hgo (*init)(hgo cthis, void (*set)(uint16 sw));

    IMPL(iGo);
};

#endif /* GO_H_ */
