#ifndef CGBASEPOINTCLOUD_H
#define CGBASEPOINTCLOUD_H

#include <vector>
#include <glm/glm.hpp>
#include "CgBase/CgBaseRenderableObject.h"

class CgBasePointCloud : public CgBaseRenderableObject
{
public:

    CgBasePointCloud();

    virtual const std::vector<glm::vec3>& getVertices()     const =0;
    virtual const std::vector<glm::vec3>& getVertexNormals() const =0;
    virtual const std::vector<glm::vec3>& getVertexColors() const =0;

};

#endif // CGBASEPOINTCLOUD_H
