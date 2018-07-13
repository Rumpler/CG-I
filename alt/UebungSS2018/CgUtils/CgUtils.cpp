#include "CgUtils.h"
#include <iostream>

CgUtils::CgUtils()
{

}

void CgUtils::printVec3(glm::vec3 *vec)
{
    std::cout << "Vec3:(" << vec->x << "," << vec->y << "," << vec->z << ")" << std::endl;
}

void CgUtils::printVec3(std::string str, glm::vec3 *vec)
{
    std::cout<< str << ":(" << vec->x << "," << vec->y << "," << vec->z << ")" << std::endl;
}

//void CgUtils::printVecVector(std::vector<glm::vec3> *vector)
//{
////    for(glm::vec3 v : vector){
////        printVec3(v);
////    }
//}

glm::vec3 CgUtils::calcFocusPointTriangle(glm::vec3 v1, glm::vec3 v2, glm::vec3 v3)
{
    return glm::vec3(   (v1.x + v2.x + v3.x) / 3.0,
                        (v1.y + v2.y + v3.y) / 3.0,
                        (v1.z + v2.z + v3.z) / 3.0);
}

glm::vec3 CgUtils::calcFaceNormal(glm::vec3 v1, glm::vec3 v2, glm::vec3 v3)
{
    glm::vec3 u = v1 - v2;
    glm::vec3 v = v3 - v2;
    glm::vec3 faceNormalTop = glm::cross(v,u);
    faceNormalTop = glm::normalize(faceNormalTop);
    return faceNormalTop;
}

glm::vec3 CgUtils::rotatePointYAxis(double angle, glm::vec3 p)
{
    return glm::vec3((p.x * cos(angle)) - (p.z * sin(angle)),
                      p.y,
                     (p.z * cos(angle)) + (p.x * sin(angle)) );
}

glm::vec3 CgUtils::multVecScalar(double scalar, glm::vec3 vec)
{
    return glm::vec3(vec.x * scalar, vec.y * scalar, vec.z * scalar);
}
