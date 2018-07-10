#include "CgObjectSelectionChangeEvent.h"

CgObjectSelectionChangeEvent::CgObjectSelectionChangeEvent():
    m_type(Cg::CgObjectSelectionChangeEvent)
{

}

Cg::EventType CgObjectSelectionChangeEvent::getType()
{
    return m_type;
}

//Remember to add objects in clone()
CgBaseEvent *CgObjectSelectionChangeEvent::clone()
{
    CgObjectSelectionChangeEvent* e = new CgObjectSelectionChangeEvent();
    e->setRenderCoordinateSystem(renderCoordinateSystem);
    e->setRenderCube(renderCube);
    e->setRenderCubeNormals(renderCubeNormals);
    e->setRenderCylinder(renderCylinder);
    e->setRenderCylinderNormals(renderCylinderNormals);
    e->setRenderRotationCurve(renderRotationCurve);
    return e;
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

bool CgObjectSelectionChangeEvent::getRenderCylinderNormals() const
{
    return renderCylinderNormals;
}

void CgObjectSelectionChangeEvent::setRenderCylinderNormals(bool value)
{
    renderCylinderNormals = value;
}

bool CgObjectSelectionChangeEvent::getRenderRotationCurve() const
{
    return renderRotationCurve;
}

void CgObjectSelectionChangeEvent::setRenderRotationCurve(bool value)
{
    renderRotationCurve = value;
}
