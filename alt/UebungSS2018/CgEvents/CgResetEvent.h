#ifndef CGRESETEVENT_H
#define CGRESETEVENT_H

#include "../CgBase/CgBaseEvent.h"
#include "../CgBase/CgEnums.h"

#include <iostream>

class CgResetEvent : public CgBaseEvent
{
public:
    CgResetEvent();

    // CgBaseEvent interface
    Cg::EventType getType();
    CgBaseEvent *clone();

private:
    Cg::EventType m_type;
};

#endif // CGRESETEVENT_H
