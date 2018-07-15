#ifndef CGBASEIMAGE_H
#define CGBASEIMAGE_H



#include <vector>
#include <glm/glm.hpp>
#include "CgBaseRenderableObject.h"


class CgBaseImage
{
public:

    virtual ~CgBaseImage(){};

    virtual int getSizeX()=0;
    virtual int getSizeY()=0;

    // Index based Pixel access (left handed coords)
    virtual glm::vec3 getPixel(int x, int y)=0;

};



#endif // CGBASEIMAGE_H

