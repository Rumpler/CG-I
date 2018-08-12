#include "CgButtonEvent.h"

bool CgButtonEvent::getBtSelectNextObject() const
{
    return btSelectNextObject;
}

void CgButtonEvent::setBtSelectNextObject(bool value)
{
    btSelectNextObject = value;
}

CgButtonEvent::CgButtonEvent() :
    m_type(Cg::CgButtonEvent)
{

}

Cg::EventType CgButtonEvent::getType()
{
    return m_type;
}

CgBaseEvent *CgButtonEvent::clone()
{
    CgButtonEvent* e = new CgButtonEvent();
    e->setBtSelectNextObject(btSelectNextObject);
    return e;
}
