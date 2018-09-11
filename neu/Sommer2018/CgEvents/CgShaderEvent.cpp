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
    ev->setNoneShader(noneShader);
    ev->setPhong(phong);
    ev->setGouraud(gouraud);
    ev->setFlat(flat);
    ev->setMaterialIndex(materialIndex);
    return ev;
}

bool CgShaderEvent::getPhong() const
{
    return phong;
}

void CgShaderEvent::setPhong(bool value)
{
    noneShader = value;
    phong = value;
    gouraud = !value;
}

bool CgShaderEvent::getGouraud() const
{
    return gouraud;
}

void CgShaderEvent::setGouraud(bool value)
{
    noneShader = value;
    phong = !value;
    gouraud = value;
}

bool CgShaderEvent::getFlat() const
{
    return flat;
}

void CgShaderEvent::setFlat(bool value)
{
    flat = value;
    smooth = !value;
}

bool CgShaderEvent::getSmooth() const
{
    return smooth;
}

void CgShaderEvent::setSmooth(bool value)
{
    smooth = value;
    flat = !value;
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

void CgShaderEvent::setNoneShader(bool value)
{
    noneShader = value;
    phong = !value;
    gouraud = !value;
}
