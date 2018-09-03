#include "CgLightsource.h"

glm::vec3 CgLightsource::getDirection() const
{
    return direction;
}

void CgLightsource::setDirection(const glm::vec3 &value)
{
    direction = value;
}


CgAppearance *CgLightsource::getAppearance() const
{
    return appearance;
}

void CgLightsource::setAppearance(CgAppearance *value)
{
    appearance = value;
}


CgLightsource::CgLightsource()
{

}

CgLightsource::CgLightsource(CgAppearance *appearance)
{
    this->appearance=appearance;
}
