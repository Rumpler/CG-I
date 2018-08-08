#ifndef CGAPPEARANCE_H
#define CGAPPEARANCE_H

#include <vector>
#include <string>
#include <glm/gtc/matrix_transform.hpp>

class CgAppearance
{
private:
    glm::vec3 object_color;
    glm::vec3 difuse_material;
public:
    CgAppearance();
    glm::vec3 getObject_color() const;
    void setObject_color(const glm::vec3 &value);
    glm::vec3 getDifuse_material() const;
    void setDifuse_material(const glm::vec3 &value);
};

#endif // CGAPPEARANCE_H
