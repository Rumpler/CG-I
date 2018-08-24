#include "CgUtils.h"
#include <iostream>


#include <stdio.h>  /* defines FILENAME_MAX */
// #define WINDOWS  /* uncomment this line to use it for windows.*/
#ifdef WINDOWS
#include <direct.h>
#define GetCurrentDir _getcwd
#else
#include <unistd.h>
#define GetCurrentDir getcwd
#endif

CgU::CgU()
{

}

void CgU::print(std::string str)
{
    std::cout << str << std::endl;
}

void CgU::print(double d)
{
    std::cout << d << std::endl;
}

void CgU::print(std::string str, double d)
{
    std::cout << str << " " << d << std::endl;
}

void CgU::print(int i)
{
    std::cout << i << std::endl;
}

void CgU::print(std::string str, int i)
{
    std::cout << str << " " << i << std::endl;
}

void CgU::print(float f)
{
    std::cout << f << std::endl;
}

void CgU::print(std::string str, float f)
{
    std::cout << str << " " << f << std::endl;
}

void CgU::print(glm::vec3 vec)
{
    std::cout << "Vec3:(" << vec.x << "," << vec.y << "," << vec.z << ")" << std::endl;
}

void CgU::print(std::string str, glm::vec3 vec)
{
    std::cout<< str << ":(" << vec.x << "," << vec.y << "," << vec.z << ")" << std::endl;
}

void CgU::print(glm::mat4 mat)
{
    std::cout << "------------------------------------" << std::endl;
    std::cout << mat[0].x << "\t" << mat[1].x << "\t" << mat[2].x << "\t" << mat[3].x << std::endl;
    std::cout << mat[0].y << "\t" << mat[1].y << "\t" << mat[2].y << "\t" << mat[3].y << std::endl;
    std::cout << mat[0].z << "\t" << mat[1].z << "\t" << mat[2].z << "\t" << mat[3].z << std::endl;
    std::cout << mat[0].w << "\t" << mat[1].w << "\t" << mat[2].w << "\t" << mat[3].w << std::endl;
    std::cout << "------------------------------------" << std::endl;
}

void CgU::print(std::string str, glm::mat4 mat)
{
    std::cout << str << std::endl;
    print(mat);
}

void CgU::printVecLength(glm::vec3 vec)
{
    std::cout << "|vec| = " << sqrt( pow(vec.x,2) + pow(vec.y,2) + pow(vec.z,2) ) << std::endl;
}

void CgU::printVecVector(std::vector<glm::vec3>* vector)
{
    std::cout << "Vector of size: " << vector->size() <<std::endl;
    for(glm::vec3 v : *(vector)){
        print(v);
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
    //setup
    glm::vec3 b = axis;
    b = glm::normalize(b);
    glm::mat4 bMat = glm::mat4(1.0f);
    bMat[3] = glm::vec4(b, 1.0f);

    //angles
    float angleInZYLevel = translateRadToDegree( acos(b.z / sqrt(pow(b.x, 2) + pow(b.z, 2)) ) );
    float angleToYAxis = translateRadToDegree( asin(b.y / 1) );

    //special cases (triangle calculation does't work because values give no triangle)
    if(b.x == 0){ angleInZYLevel = 0; }
    if(b.z == 0){ angleInZYLevel = 90; }
    if(b.y == 0){ angleToYAxis = 90; }
    if(b.x == 0 && b.z == 0){ angleInZYLevel = 0; angleToYAxis = 0; }

//    std::cout << "angleInZYLevel: " << angleInZYLevel << ", angleToYAxis: " << angleToYAxis << std::endl;

    glm::mat4 result = tRotateMatY(angleInZYLevel) * tRotateMatX(angleToYAxis) * tRotateMatY(angle) * tRotateMatX(-angleToYAxis) * tRotateMatY(-angleInZYLevel);

    //TEMP FIX ABOVE AND DELETE LATER
        result = glm::mat4(1.0f);
        result = glm::rotate(result, translateDegreeToRad(angle), axis);

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

glm::mat4 CgU::tScaleMat(float x, float y, float z)
{
    return tScaleMat(glm::vec3(x,y,z));
}

glm::mat4 CgU::tTranslateMat(glm::vec3 vec)
{
    glm::mat4 result = glm::mat4(1.0f);
    result[3] = glm::vec4(vec,1);
    return result;
}

glm::mat4 CgU::tTranslateMat(float x, float y, float z)
{
    return tTranslateMat(glm::vec3(x,y,z));
}

void CgU::addTransformation(CgSceneGraphEntity *entity, glm::mat4 transformation)
{
    //TODO BUG ?

    glm::mat4 mat = entity->getCurrentTransformation();
    glm::vec3 translationVec = mat[3];
    mat[3] = glm::vec4(glm::vec3(0.0f), mat[3].w);
    mat = mat * glm::inverse(mat) * transformation * mat;
    mat[3] = mat[3] + glm::vec4(translationVec, 0);
    entity->setCurrentTransformation(mat);
}

float CgU::translateDegreeToRad(float degree)
{
    return (2.0 * M_PI / 360.0) * degree;
}

float CgU::translateRadToDegree(float rad)
{
    return (360.0 / ( 2 * M_PI) ) * rad;
}

std::string CgU::getCurrentDirectory()
{
    char buff[FILENAME_MAX];
    GetCurrentDir( buff, FILENAME_MAX );
    std::string current_working_dir(buff);
    return current_working_dir;
}

std::string CgU::getParentDirectory()
{
    std::string result= getCurrentDirectory();
    result.erase(result.end()-30,result.end());
    return result;
}
