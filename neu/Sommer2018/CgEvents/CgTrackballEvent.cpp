#include "CgTrackballEvent.h"
#include <glm/glm.hpp>

CgTrackballEvent::CgTrackballEvent()
{
  m_type=Cg::CgTrackballEvent;
}

CgBaseEvent* CgTrackballEvent::clone()
{
    return new CgTrackballEvent(m_type,m_rotation);
}

Cg::EventType  CgTrackballEvent::getType()
{
    return m_type;
}


std::ostream& operator<<(std::ostream& os,const CgTrackballEvent& e)
{
    os << "CgTrackballEvent: "<< std::endl;
    return os;
}




CgTrackballEvent::CgTrackballEvent(Cg::EventType type, glm::mat4 rot)
{
    m_type=type;
    m_rotation=rot;
}

