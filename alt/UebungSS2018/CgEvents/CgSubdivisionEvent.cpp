#include "CgSubdivisionEvent.h"

CgSubdivisionEvent::CgSubdivisionEvent():
    m_type(Cg::CgSubdivisionEvent)
{

}

Cg::EventType CgSubdivisionEvent::getType()
{
    return m_type;
}

CgBaseEvent *CgSubdivisionEvent::clone()
{
    CgSubdivisionEvent* e = new CgSubdivisionEvent();

    return e;
}

std::ostream& operator<<(std::ostream &os, const CgSubdivisionEvent &e)
{
    os << "CgSubdivisionEvent-Event of Type: "<< e.m_type << std::endl;
    return os;
}
