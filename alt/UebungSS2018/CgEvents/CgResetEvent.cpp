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
    e->setResetCylinder(resetCylinder);
    e->setResetRotationCurve(resetRotationCurve);

    return e;
}

bool CgResetEvent::getResetCylinder() const
{
    return resetCylinder;
}

void CgResetEvent::setResetCylinder(bool value)
{
    resetCylinder = value;
}

bool CgResetEvent::getResetRotationCurve() const
{
    return resetRotationCurve;
}

void CgResetEvent::setResetRotationCurve(bool value)
{
    resetRotationCurve = value;
}
