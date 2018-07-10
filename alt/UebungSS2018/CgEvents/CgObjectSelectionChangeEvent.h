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

    bool getRenderTriangle() const;
    void setRenderTriangle(bool value);

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

private:
    Cg::EventType m_type;

    bool renderCoordinateSystem;
    bool renderTriangle;
    bool renderCube;
    bool renderCubeNormals;
    bool renderCylinder;
    bool renderCylinderNormals;
};

#endif // CGOBJECTSELECTIONCHANGEEVENT_H
