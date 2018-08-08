#include "CgAppearance.h"

#include <CgUtils/CgUtils.h>
#include <iostream>


CgAppearance::CgAppearance()
{
    object_color = glm::vec3(0.0f, 0.0f, 1.0f);
}

glm::vec3 CgAppearance::getObjectColor() const
{
    return glm::vec3(object_color);
}

void CgAppearance::setObjectColor(const glm::vec3 &value)
{
    object_color = glm::vec3(value);
}

//glm::vec3 CgAppearance::getDifuse_material() const
//{
//    return difuse_material;
//}

//void CgAppearance::setDifuse_material(const glm::vec3 &value)
//{
//    difuse_material = value;
//}


