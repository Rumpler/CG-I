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
    this->appearance=new CgAppearance();
    appearance->setSpecular(glm::vec4(1.,1.,1.,1.));
    appearance->setDiffuse(glm::vec4(.5,.5,.5,1.));
    appearance->setAmbiente(glm::vec4(.2,.2,.2,1.));
    direction=glm::vec3(0,0,3);
}

CgLightsource::CgLightsource(CgAppearance *appearance)
{
    this->appearance=appearance;
}
