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
    e->setForPointScheme(forPointScheme);
    return e;
}

bool CgSubdivisionEvent::getForPointScheme() const
{
    return forPointScheme;
}

void CgSubdivisionEvent::setForPointScheme(bool value)
{
    forPointScheme = value;
}

std::ostream& operator<<(std::ostream &os, const CgSubdivisionEvent &e)
{
    os << "CgSubdivisionEvent-Event of Type: "<< e.m_type << std::endl;
    return os;
}
