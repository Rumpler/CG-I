#ifndef CGUTILS_H
#define CGUTILS_H

#include <glm/gtc/matrix_transform.hpp>
#include <string>

class CgUtils
{
public:
    CgUtils();

    void static printVec3(glm::vec3* vec);
    void static printVec3(std::string str, glm::vec3* vec);
};

#endif // CGUTILS_H
