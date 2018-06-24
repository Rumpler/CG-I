#include "CgObjectSelectionChangeEvent.h"

CgObjectSelectionChangeEvent::CgObjectSelectionChangeEvent():
    m_type(Cg::CgObjectSelectionChangeEvent)
{

}

Cg::EventType CgObjectSelectionChangeEvent::getType()
{
    return m_type;
}

CgBaseEvent *CgObjectSelectionChangeEvent::clone()
{
    CgObjectSelectionChangeEvent* e = new CgObjectSelectionChangeEvent();
    e->setRenderCoordinateSystem(renderCoordinateSystem);
    e->setRenderCube(renderCube);
    e->setRenderTriangle(renderTriangle);
    return e;
}

bool CgObjectSelectionChangeEvent::getRenderTriangle() const
{
    return renderTriangle;
}

void CgObjectSelectionChangeEvent::setRenderTriangle(bool value)
{
    renderTriangle = value;
}

bool CgObjectSelectionChangeEvent::getRenderCube() const
{
    return renderCube;
}

void CgObjectSelectionChangeEvent::setRenderCube(bool value)
{
    renderCube = value;
}

bool CgObjectSelectionChangeEvent::getRenderCoordinateSystem() const
{
    return renderCoordinateSystem;
}

void CgObjectSelectionChangeEvent::setRenderCoordinateSystem(bool value)
{
    renderCoordinateSystem = value;
}
