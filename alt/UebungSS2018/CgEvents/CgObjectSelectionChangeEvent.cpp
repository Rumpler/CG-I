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
    e->setRenderTriangle(renderTriangle);
    e->setRenderCube(renderCube);
    e->setRenderCubeNormals(renderCubeNormals);
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

bool CgObjectSelectionChangeEvent::getRenderCubeNormals() const
{
    return renderCubeNormals;
}

void CgObjectSelectionChangeEvent::setRenderCubeNormals(bool value)
{
    renderCubeNormals = value;
}

bool CgObjectSelectionChangeEvent::getRenderCylinder() const
{
    return renderCylinder;
}

void CgObjectSelectionChangeEvent::setRenderCylinder(bool value)
{
    renderCylinder = value;
}
