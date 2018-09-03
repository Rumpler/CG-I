#ifndef LIGHTSOURCE_H
#define LIGHTSOURCE_H
#include <glm/common.hpp>
#include "CgSceneGraph/CgAppearance.h"
/**
    m_renderer->setUniformValue("lightDiffuseColor",glm::vec3(1.0));
    m_renderer->setUniformValue("lightAmbientColor",glm::vec4(1.0,1.0,1.0,1.0));
    m_renderer->setUniformValue("lightSpecularColor",glm::vec4(1.0,1.0,1.0,1.0));
 * @brief The LightSource class
 */
class CgLightsource
{

private: glm::vec3 direction;
     CgAppearance *appearance;

public:
    CgLightsource();
    CgLightsource(CgAppearance * appearance);
    CgAppearance *getAppearance() const;
    void setAppearance(CgAppearance *value);
    glm::vec3 getDirection() const;
    void setDirection(const glm::vec3 &value);
};

#endif // LIGHTSOURCE_H
