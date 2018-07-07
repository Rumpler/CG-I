#include "CgResetEvent.h"

CgResetEvent::CgResetEvent():
    m_type(Cg::CgResetEvent)
{

}

Cg::EventType CgResetEvent::getType()
{
    return m_type;
}

CgBaseEvent *CgResetEvent::clone()
{
    CgResetEvent* e = new CgResetEvent();

    return e;
}
