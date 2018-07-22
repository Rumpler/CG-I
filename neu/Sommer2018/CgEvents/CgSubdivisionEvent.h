#ifndef CGSUBDIVISIONEVENT_H
#define CGSUBDIVISIONEVENT_H

#include <CgBase/CgBaseEvent.h>
#include <iostream>



class CgSubdivisionEvent : public CgBaseEvent
{
public:
    CgSubdivisionEvent();

    // CgBaseEvent interface
    Cg::EventType getType();
    CgBaseEvent *clone();

    friend std::ostream& operator <<(std::ostream& os, const CgSubdivisionEvent& e);

    bool getForPointScheme() const;
    void setForPointScheme(bool value);

private:
    Cg::EventType m_type;

    bool forPointScheme = false;
};

#endif // CGSUBDIVISIONEVENT_H
