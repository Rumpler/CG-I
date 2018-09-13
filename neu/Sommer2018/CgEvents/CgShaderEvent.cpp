#include "CgShaderEvent.h"

CgShaderEvent::CgShaderEvent() :
    m_type(Cg::CgShaderEvent)
{

}

Cg::EventType CgShaderEvent::getType()
{
    return m_type;
}

CgBaseEvent *CgShaderEvent::clone()
{
    CgShaderEvent* ev = new CgShaderEvent();
    ev->noneShader = noneShader;
    ev->phong = phong;
    ev->gouraud = gouraud;
    ev->flat = flat;
    ev->smooth = smooth;
    ev->materialIndex = materialIndex;

    return ev;
}

bool CgShaderEvent::getPhong() const
{
    return phong;
}

void CgShaderEvent::setPhong()
{
    noneShader = false;
    phong = true;
    gouraud = false;
}

bool CgShaderEvent::getGouraud() const
{
    return gouraud;
}

void CgShaderEvent::setGouraud()
{
    noneShader = false;
    phong = false;
    gouraud = true;
}

bool CgShaderEvent::getFlat() const
{
    return flat;
}

void CgShaderEvent::setFlat()
{
    flat = true;
    smooth = false;
}

bool CgShaderEvent::getSmooth() const
{
    return smooth;
}

void CgShaderEvent::setSmooth()
{
    smooth = true;
    flat = false;
}

int CgShaderEvent::getMaterialIndex() const
{
    return materialIndex;
}

void CgShaderEvent::setMaterialIndex(int value)
{
    materialIndex = value;
}

bool CgShaderEvent::getNoneShader() const
{
    return noneShader;
}

void CgShaderEvent::setNoneShader()
{
    noneShader = true;
    phong = false;
    gouraud = false;
}
