#ifndef CGBASEPOLYLINE_H
#define CGBASEPOLYLINE_H

#include <vector>
#include <glm/glm.hpp>
#include "CgBaseRenderableObject.h"


class CgBasePolyline : public CgBaseRenderableObject
{
public:
    virtual ~CgBasePolyline(){};

    virtual const std::vector<glm::vec3>& getVertices()  const=0;
    virtual glm::vec3               getColor()     const=0;
    virtual unsigned int            getLineWidth() const=0;
};

#endif // CGBASEPOLYLINE_H
