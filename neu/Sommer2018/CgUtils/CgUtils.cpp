#include "CgUtils.h"
#include <iostream>

CgU::CgU()
{

}

void CgU::printVec3(glm::vec3 vec)
{
    std::cout << "Vec3:(" << vec.x << "," << vec.y << "," << vec.z << ")" << std::endl;
}

void CgU::printVec3(std::string str, glm::vec3 vec)
{
    std::cout<< str << ":(" << vec.x << "," << vec.y << "," << vec.z << ")" << std::endl;
}

void CgU::printMat4(glm::mat4 mat)
{
    std::cout << "------------------------------------" << std::endl;
    std::cout << mat[0].x << "\t" << mat[1].x << "\t" << mat[2].x << "\t" << mat[3].x << std::endl;
    std::cout << mat[0].y << "\t" << mat[1].y << "\t" << mat[2].y << "\t" << mat[3].y << std::endl;
    std::cout << mat[0].z << "\t" << mat[1].z << "\t" << mat[2].z << "\t" << mat[3].z << std::endl;
    std::cout << mat[0].w << "\t" << mat[1].w << "\t" << mat[2].w << "\t" << mat[3].w << std::endl;
    std::cout << "------------------------------------" << std::endl;
}

void CgU::printMat4(std::string str, glm::mat4 mat)
{
    std::cout << str << std::endl;
    printMat4(mat);
}

void CgU::printVecVector(std::vector<glm::vec3>* vector)
{
    std::cout << "Vector of size: " << vector->size() <<std::endl;
    for(glm::vec3 v : *(vector)){
        printVec3(v);
    }
}

glm::vec3 CgU::calcFocusPointTriangle(glm::vec3 v1, glm::vec3 v2, glm::vec3 v3)
{
    return glm::vec3(   (v1.x + v2.x + v3.x) / 3.0,
                        (v1.y + v2.y + v3.y) / 3.0,
                        (v1.z + v2.z + v3.z) / 3.0);
}

glm::vec3 CgU::calcFaceNormal(glm::vec3 v1, glm::vec3 v2, glm::vec3 v3)
{
    glm::vec3 u = v1 - v2;
    glm::vec3 v = v3 - v2;
    glm::vec3 faceNormalTop = glm::cross(v,u);
    faceNormalTop = glm::normalize(faceNormalTop);
    return faceNormalTop;
}

glm::vec3 CgU::rotatePointYAxis(double angle, glm::vec3 p)
{
    return glm::vec3((p.x * cos(angle)) - (p.z * sin(angle)),
                      p.y,
                     (p.z * cos(angle)) + (p.x * sin(angle)) );
}

glm::vec3 CgU::multVecScalar(double scalar, glm::vec3 vec)
{
    return glm::vec3(vec.x * scalar, vec.y * scalar, vec.z * scalar);
}

glm::mat4 CgU::tRotateMatZ(float angle)
{
    angle = translateDegreeToRad(angle);
    glm::mat4 result = glm::mat4(1.0f);
    result[0] = glm::vec4(cos(angle), sin(angle), 0, 0);
    result[1] = glm::vec4(-sin(angle), cos(angle), 0, 0);
    return result;
}

glm::mat4 CgU::tRotateMatX(float angle)
{
    angle = translateDegreeToRad(angle);
    glm::mat4 result = glm::mat4(1.0f);
    result[1] = glm::vec4(0, cos(angle), sin(angle), 0);
    result[2] = glm::vec4(0, -sin(angle), cos(angle), 0);
    return result;
}

glm::mat4 CgU::tRotateMatY(float angle)
{
    angle = translateDegreeToRad(angle);
    glm::mat4 result = glm::mat4(1.0f);
    result[0] = glm::vec4(cos(angle), 0, -sin(angle), 0);
    result[2] = glm::vec4(sin(angle), 0, cos(angle), 0);
    return result;
}

glm::mat4 CgU::tRotateMat(glm::vec3 axis, float angle)
{
    //TODO untested, maybe mixed degree and rad, test and fix later

    float angleZ = acos( axis.x / sqrt(axis.x * axis.x + axis.b * axis.b) );
    float angleY = acos( axis.z );

    glm::mat4 result = tTranslateMat(axis) * tRotateMatZ(angleZ) * tRotateMatY(angleY)
                        * tRotateMatZ(angle) * tRotateMatY(-angleY) * tRotateMatZ(-angleZ)
                        * tTranslateMat(glm::vec3(- axis.x, -axis.y, - axis.z));
    return result;

}

glm::mat4 CgU::tScaleMat(glm::vec3 factor)
{
    glm::mat4 result = glm::mat4(1.0f);
    result[0].x = factor.x;
    result[1].y = factor.y;
    result[2].z = factor.z;

    return result;
}

glm::mat4 CgU::tTranslateMat(glm::vec3 vec)
{
    glm::mat4 result = glm::mat4(1.0f);
    result[3] = glm::vec4(vec,1);
    return result;
}

float CgU::translateDegreeToRad(float degree)
{
    return (2.0 * M_PI / 360.0) * degree;
}
