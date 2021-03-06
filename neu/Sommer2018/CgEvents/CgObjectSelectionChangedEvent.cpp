#include "CgObjectSelectionChangedEvent.h"

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
    e->setRenderRotationBody(renderRotationBody);
    e->setRenderRotationBodyNormals(renderRotationBodyNormals);
    e->setRenderLoadedObject(renderLoadedObject);
    e->setRenderLoadedObjectNormals(renderLoadedObjectNormals);
    e->setRenderCustomRotationAxis(renderCustomRotationAxis);
    e->setRenderScene(renderScene);
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

bool CgObjectSelectionChangeEvent::getRenderRotationBody() const
{
    return renderRotationBody;
}

void CgObjectSelectionChangeEvent::setRenderRotationBody(bool value)
{
    renderRotationBody = value;
}

bool CgObjectSelectionChangeEvent::getRenderLoadedObject() const
{
    return renderLoadedObject;
}

void CgObjectSelectionChangeEvent::setRenderLoadedObject(bool value)
{
    renderLoadedObject = value;
}

bool CgObjectSelectionChangeEvent::getRenderLoadedObjectNormals() const
{
    return renderLoadedObjectNormals;
}

void CgObjectSelectionChangeEvent::setRenderLoadedObjectNormals(bool value)
{
    renderLoadedObjectNormals = value;
}

bool CgObjectSelectionChangeEvent::getRenderRotationBodyNormals() const
{
    return renderRotationBodyNormals;
}

void CgObjectSelectionChangeEvent::setRenderRotationBodyNormals(bool value)
{
    renderRotationBodyNormals = value;
}

bool CgObjectSelectionChangeEvent::getRenderCustomRotationAxis() const
{
    return renderCustomRotationAxis;
}

void CgObjectSelectionChangeEvent::setRenderCustomRotationAxis(bool value)
{
    renderCustomRotationAxis = value;
}

bool CgObjectSelectionChangeEvent::getRenderScene() const
{
    return renderScene;
}

void CgObjectSelectionChangeEvent::setRenderScene(bool value)
{
    renderScene = value;
}
