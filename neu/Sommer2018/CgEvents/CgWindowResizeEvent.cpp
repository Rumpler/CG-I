#include "CgWindowResizeEvent.h"

CgWindowResizeEvent::CgWindowResizeEvent():
m_type(Cg::WindowResizeEvent),
m_w(0),
m_h(0)
{

}


CgWindowResizeEvent::CgWindowResizeEvent(Cg::EventType type,int w, int h):
m_type(type),
m_w(w),
m_h(h)
{

}



CgBaseEvent* CgWindowResizeEvent::clone()
{
    return new CgWindowResizeEvent(m_type,m_w,m_h);
}

Cg::EventType  CgWindowResizeEvent::getType()
{
    return m_type;
}

unsigned int CgWindowResizeEvent::w()
{
    return m_w;
}

unsigned int CgWindowResizeEvent::h()
{
    return m_h;
}


std::ostream& operator<<(std::ostream& os,const CgWindowResizeEvent& e)
{
    os << "WindowResize-Event of Type: "<< e.m_type <<", w:" << e.m_w  <<", h:" << e.m_h  << std::endl;
    return os;
}
