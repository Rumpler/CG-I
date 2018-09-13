#ifndef CGAPPEARANCE_H
#define CGAPPEARANCE_H

#include <vector>
#include <string>
#include <glm/gtc/matrix_transform.hpp>

class CgAppearance
{
private:

    //DON
    glm::vec4 material;
    glm::vec4 ambiente;
    glm::vec4 diffuse;
    glm::vec4 specular;
    float shininess;
    glm::vec4 color = glm::vec4(0.0f, 0.45f, 0.5f, 1.0f);
public:
    CgAppearance();

//    glm::vec3 getDifuse_material() const;
//    void setDifuse_material(const glm::vec3 &value);
    glm::vec4 getAmbiente() const;
    void setAmbiente(const glm::vec4 &value);
    glm::vec4 getDiffuse() const;
    void setDiffuse(const glm::vec4 &value);
    glm::vec4 getSpecular() const;
    void setSpecular(const glm::vec4 &value);
    glm::vec4 getColor() const;
    void setColor(const glm::vec4 &value);
    glm::vec4 getMaterial() const;
    void setMaterial(const glm::vec4 &value);
    float getShininess() const;
    void setShininess(float value);
};

#endif // CGAPPEARANCE_H
