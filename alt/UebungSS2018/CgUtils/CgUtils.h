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

    glm::vec3 static calcFocusPointTriangle(glm::vec3 v1, glm::vec3 v2, glm::vec3 v3);
    glm::vec3 static calcFaceNormal(glm::vec3 v1, glm::vec3 v2, glm::vec3 v3);

    glm::vec3 static rotatePointYAxis(double angle, glm::vec3 p);

    glm::vec3 static multVecScalar(double scalar, glm::vec3 vec);
};

#endif // CGUTILS_H
