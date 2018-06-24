/*
 * CgBaseEvent.h
 *
 *  Created on: 16.02.2012
 *      Author: ginkel
 */

#ifndef CGBASEEVENT_H_
#define CGBASEEVENT_H_

#include <cstdlib>
#include "CgEnums.h"




class CgBaseEvent {
public:



    CgBaseEvent();


    virtual ~CgBaseEvent(){};
    virtual Cg::EventType getType()=0;
    virtual CgBaseEvent* clone()=0;


protected:


};

inline CgBaseEvent::CgBaseEvent()
{
};

#endif /* CGBASEEVENT_H_ */
