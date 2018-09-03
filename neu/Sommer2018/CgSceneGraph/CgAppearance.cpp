#include "CgAppearance.h"

#include <CgUtils/CgUtils.h>
#include <iostream>


glm::vec4 CgAppearance::getAmbiente() const
{
    return ambiente;
}

void CgAppearance::setAmbiente(const glm::vec4 &value)
{
    ambiente = value;
}

glm::vec4 CgAppearance::getDiffuse() const
{
    return diffuse;
}

void CgAppearance::setDiffuse(const glm::vec4 &value)
{
    diffuse = value;
}

glm::vec4 CgAppearance::getSpecular() const
{
    return specular;
}

void CgAppearance::setSpecular(const glm::vec4 &value)
{
    specular = value;
}

glm::vec3 CgAppearance::getObjectColor() const
{
    return object_color;
}

void CgAppearance::setObjectColor(const glm::vec3 &value)
{
    object_color = value;
}

glm::vec4 CgAppearance::getColor() const
{
    return color;
}

void CgAppearance::setColor(const glm::vec4 &value)
{
    color = value;
}

glm::vec4 CgAppearance::getMaterial() const
{
    return material;
}

void CgAppearance::setMaterial(const glm::vec4 &value)
{
    material = value;
}

CgAppearance::CgAppearance()
{
    object_color = glm::vec3(0.0f, 0.0f, 1.0f);
}



