#ifndef CGOBJECTSELECTIONCHANGEEVENT_H
#define CGOBJECTSELECTIONCHANGEEVENT_H

#include "../CgBase/CgBaseEvent.h"
#include "../CgBase/CgEnums.h"

class CgObjectSelectionChangeEvent : public CgBaseEvent
{
public:
    CgObjectSelectionChangeEvent();

    // CgBaseEvent interface
public:
    Cg::EventType getType();
    CgBaseEvent *clone();

    bool getRenderCube() const;
    void setRenderCube(bool value);

    bool getRenderCoordinateSystem() const;
    void setRenderCoordinateSystem(bool value);

    bool getRenderCubeNormals() const;
    void setRenderCubeNormals(bool value);

    bool getRenderCylinder() const;
    void setRenderCylinder(bool value);

    bool getRenderCylinderNormals() const;
    void setRenderCylinderNormals(bool value);

    bool getRenderRotationCurve() const;
    void setRenderRotationCurve(bool value);

    bool getRenderRotationBody() const;
    void setRenderRotationBody(bool value);

    bool getRenderLoadedObject() const;
    void setRenderLoadedObject(bool value);

    bool getRenderLoadedObjectNormals() const;
    void setRenderLoadedObjectNormals(bool value);

private:
    Cg::EventType m_type;

    bool renderCoordinateSystem;
    bool renderCube;
    bool renderCubeNormals;
    bool renderCylinder;
    bool renderCylinderNormals;
    bool renderRotationCurve;
    bool renderRotationBody;
    bool renderLoadedObject;
    bool renderLoadedObjectNormals;
};

#endif // CGOBJECTSELECTIONCHANGEEVENT_H
