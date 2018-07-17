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

    bool getResetCylinder() const;
    void setResetCylinder(bool value);

    bool getResetRotationCurve() const;
    void setResetRotationCurve(bool value);

private:
    Cg::EventType m_type;

    bool resetCylinder = false;
    bool resetRotationCurve = false;
};

#endif // CGRESETEVENT_H
