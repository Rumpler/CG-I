#ifndef CGWINDOWRESIZEEVENT_H
#define CGWINDOWRESIZEEVENT_H

#include "../CgBase/CgBaseEvent.h"
#include "../CgBase/CgEnums.h"


#include <iostream>

class CgWindowResizeEvent : public CgBaseEvent
{
public:
    CgWindowResizeEvent();
    CgWindowResizeEvent(Cg::EventType type, int w, int h);
    ~CgWindowResizeEvent(){};

    //inherited
    Cg::EventType  getType();
    CgBaseEvent* clone();

    unsigned int w();
    unsigned int h();

    friend std::ostream& operator <<(std::ostream& os, const CgWindowResizeEvent& e);

private:
     Cg::EventType m_type;
     unsigned int m_w;
     unsigned int m_h;

};

#endif // CGWINDOWRESIZEEVENT_H
