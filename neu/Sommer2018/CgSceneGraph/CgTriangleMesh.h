#ifndef CGTRIANGLEMESH_H
#define CGTRIANGLEMESH_H

#include <CgBase/CgBaseTriangleMesh.h>



class CgTriangleMesh : public virtual CgBaseTriangleMesh
{
public:
    CgTriangleMesh();

    virtual const glm::vec3 getColor() const;
    virtual void setColor(glm::vec3 color);
};


#endif // CGTRIANGLEMESH_H
