#include "CgLoadObjFileEvent.h"





CgBaseEvent* CgLoadObjFileEvent::clone()
{
    return new CgLoadObjFileEvent(m_type,m_filename);
}

Cg::EventType  CgLoadObjFileEvent::getType()
{
    return m_type;
}


std::ostream& operator<<(std::ostream& os,const CgLoadObjFileEvent& e)
{
    os << "LoadObjFileEvent: "<< e.m_filename<< std::endl;
    return os;
}




CgLoadObjFileEvent::CgLoadObjFileEvent(Cg::EventType type, std::string filename)
{
    m_type=type;
    m_filename=filename;
}


CgLoadObjFileEvent::CgLoadObjFileEvent()
{
    m_type=Cg::LoadObjFileEvent;
}


