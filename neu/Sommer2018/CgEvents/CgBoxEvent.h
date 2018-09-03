#ifndef CGBOXEVENT_H
#define CGBOXEVENT_H


#include "CgBase/CgBaseEvent.h"
class CgBoxEvent : public CgBaseEvent
{

private: enum Cg::EventType type;
    float selected;
public:
    CgBoxEvent();

    CgBoxEvent(const enum Cg::EventType type, const float selected);

    // CgBaseEvent interface
public:
    Cg::EventType getType();
    CgBaseEvent *clone();
    float getSelected() const;
    void setSelected(float value);
};
#endif // CGBOXEVENT_H
