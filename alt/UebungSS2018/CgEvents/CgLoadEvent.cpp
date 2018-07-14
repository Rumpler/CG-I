#include "CgLoadEvent.h"

CgLoadEvent::CgLoadEvent():
    m_type(Cg::CgLoadEvent)
{

}

Cg::EventType CgLoadEvent::getType()
{
    return m_type;
}

CgBaseEvent *CgLoadEvent::clone()
{
    CgLoadEvent *e = new CgLoadEvent();
    e->setFilename(filename);
    return e;
}

std::string CgLoadEvent::getFilename() const
{
    return filename;
}

void CgLoadEvent::setFilename(const std::string &value)
{
    filename = value;
}
