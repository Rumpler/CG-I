#ifndef CGUTILS_H
#define CGUTILS_H

#include <CgSceneGraph/CgSceneGraphEntity.h>
#include <glm/gtc/matrix_transform.hpp>
#include <string>
#include <vector>

class CgU
{
public:
    CgU();

    void static printVec3(glm::vec3 vec);
    void static printVec3(std::string str, glm::vec3 vec);
    void static printMat4(glm::mat4 mat);
    void static printMat4(std::string str, glm::mat4 mat);

    void static printVecVector(std::vector<glm::vec3>* vector);

    glm::vec3 static calcFocusPointTriangle(glm::vec3 v1, glm::vec3 v2, glm::vec3 v3);
    glm::vec3 static calcFaceNormal(glm::vec3 v1, glm::vec3 v2, glm::vec3 v3);

    glm::vec3 static rotatePointYAxis(double angle, glm::vec3 p);

    glm::vec3 static multVecScalar(double scalar, glm::vec3 vec);

    glm::mat4 static tRotateMatZ(float angle);
    glm::mat4 static tRotateMatX(float angle);
    glm::mat4 static tRotateMatY(float angle);
    glm::mat4 static tRotateMat(glm::vec3 axis, float angle);
    glm::mat4 static tScaleMat(glm::vec3 factor);
    glm::mat4 static tScaleMat(float x, float y, float z);
    glm::mat4 static tTranslateMat(glm::vec3 vec);
    glm::mat4 static tTranslateMat(float x, float y, float z);

    void static addTransformation(CgSceneGraphEntity* entity, glm::mat4 transformation);

    float static translateDegreeToRad(float degree);
    float static translateRadToDegree(float rad);

    std::string static getCurrentDirectory();
    std::string static getParentDirectory();




};

#endif // CGUTILS_H
