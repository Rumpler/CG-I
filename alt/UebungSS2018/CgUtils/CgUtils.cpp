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
