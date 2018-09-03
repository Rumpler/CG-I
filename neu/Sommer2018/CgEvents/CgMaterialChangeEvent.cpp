#include "CgMaterialChangeEvent.h"

CgMaterialChangeEvent::CgMaterialChangeEvent(): type(Cg::EventType::CgChangeMaterial)
{

}

CgMaterialChangeEvent::CgMaterialChangeEvent(glm::vec4 mat, glm::vec4 amb, glm::vec4 diffuse, float scalar, enum Cg::EventType type)
{
    this->amb=amb;
    this->diffuse=diffuse;
    this->mat=mat;
    this->scalar = scalar;
    this->type = type;
}

float CgMaterialChangeEvent::getScalar() const
{
    return scalar;
}

void CgMaterialChangeEvent::setScalar(float value)
{
    scalar = value;
}

glm::vec4 CgMaterialChangeEvent::getDiffuse() const
{
    return diffuse;
}

void CgMaterialChangeEvent::setDiffuse(const glm::vec4 &value)
{
    diffuse = value;
}

glm::vec4 CgMaterialChangeEvent::getAmb() const
{
    return amb;
}

void CgMaterialChangeEvent::setAmb(const glm::vec4 &value)
{
    amb = value;
}

glm::vec4 CgMaterialChangeEvent::getMat() const
{
    return mat;
}

void CgMaterialChangeEvent::setMat(const glm::vec4 &value)
{
    mat = value;
}

Cg::EventType CgMaterialChangeEvent::getType()
{
    return type;
}

CgBaseEvent *CgMaterialChangeEvent::clone()
{
    return new CgMaterialChangeEvent(mat,amb,diffuse,scalar,type);
}
