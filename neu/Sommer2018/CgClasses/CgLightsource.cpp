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
    appearance->setSpecular(glm::vec4(1.f,1.f,1.f,1.f));
    appearance->setDiffuse(glm::vec4(.5f,.5f,.5f,1.f));
    appearance->setAmbiente(glm::vec4(.2f,.2f,.2f,1.f));
    direction=glm::vec3(0.f,0.f,2.f);
}

CgLightsource::CgLightsource(CgAppearance *appearance)
{
    this->appearance=appearance;
}
