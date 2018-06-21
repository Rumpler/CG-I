#include "CgKeyEvent.h"

CgKeyEvent::CgKeyEvent()
{

}

CgKeyEvent::CgKeyEvent(Cg::EventType type,Cg::Key key,Cg::KeyboardModifiers mod, std::string text)
{
    m_type=type;
    m_key=key;
    m_mod=mod;
    m_text=text;
}

CgBaseEvent* CgKeyEvent::clone()
{
    return new CgKeyEvent(m_type,m_key,m_mod,m_text);
}

Cg::EventType  CgKeyEvent::getType()
{
    return m_type;
}


Cg::KeyboardModifiers CgKeyEvent::modifiers() const
{
    return m_mod;
}

Cg::Key CgKeyEvent::key() const
{
    return m_key;
}

std::string CgKeyEvent::text() const
{
    return m_text;
}

std::ostream& operator<<(std::ostream& os,const CgKeyEvent& e)
{
    os << "Key-Event of Type: "<< e.m_type <<", Key: "<< e.m_key<<", Modifier: "<< e.m_mod<<", Text: "<< e.m_text;
    return os;
}
