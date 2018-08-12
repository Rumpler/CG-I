#ifndef CGBUTTONEVENT_H
#define CGBUTTONEVENT_H

#include <CgBase/CgBaseEvent.h>



class CgButtonEvent : public CgBaseEvent
{
private:
    Cg::EventType m_type;

    bool btSelectNextObject = false;

public:
    CgButtonEvent();

    Cg::EventType getType();
    CgBaseEvent *clone();

    bool getBtSelectNextObject() const;
    void setBtSelectNextObject(bool value);
};

#endif // CGBUTTONEVENT_H
