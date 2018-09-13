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

    //Print methods for all kind of signatures
    void static print(bool d);
    void static print(std::string str, bool d);
    void static print(std::string str);
    void static print(double d);
    void static print(std::string str, double d);
    void static print(int i);
    void static print(std::string str, int i);
    void static print(float f);
    void static print(std::string str, float f);
    void static print(glm::vec3 vec);
    void static print(std::string str, glm::vec3 vec);
    void static print(glm::vec4 vec);
    void static print(std::string str, glm::vec4 vec);
    void static print(glm::mat4 mat);
    void static print(std::string str, glm::mat4 mat);
    void static printVecLength(glm::vec3 vec);
    void static printVecVector(std::vector<glm::vec3>* vector);

    //Translate methods
    glm::mat4 static tRotateMatZ(float angle);
    glm::mat4 static tRotateMatX(float angle);
    glm::mat4 static tRotateMatY(float angle);
    glm::mat4 static tRotateMat(glm::vec3 axis, float angle);
    glm::mat4 static tScaleMat(glm::vec3 factor);
    glm::mat4 static tScaleMat(float x, float y, float z);
    glm::mat4 static tTranslateMat(glm::vec3 vec);
    glm::mat4 static tTranslateMat(float x, float y, float z);

    //Helper
    float static translateDegreeToRad(float degree);
    float static translateRadToDegree(float rad);

    std::string static getCurrentDirectory(); //.../Sommer2018/build...
    std::string static getParentDirectory(); // .../Sommer2018/

    void static addTransformation(CgSceneGraphEntity* entity, glm::mat4 transformation);

    glm::vec3 static calcFocusPointTriangle(glm::vec3 v1, glm::vec3 v2, glm::vec3 v3);
    glm::vec3 static calcFaceNormal(glm::vec3 v1, glm::vec3 v2, glm::vec3 v3);

    glm::vec3 static rotatePointYAxis(double angle, glm::vec3 p);
    glm::vec3 static multVecScalar(double scalar, glm::vec3 vec);


};

#endif // CGUTILS_H
