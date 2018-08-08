#include "CgAppearance.h"

glm::vec3 CgAppearance::getObject_color() const
{
    return object_color;
}

void CgAppearance::setObject_color(const glm::vec3 &value)
{
    object_color = value;
}

glm::vec3 CgAppearance::getDifuse_material() const
{
    return difuse_material;
}

void CgAppearance::setDifuse_material(const glm::vec3 &value)
{
    difuse_material = value;
}

CgAppearance::CgAppearance()
{

}
