#ifndef CGCYLINDER_H
#define CGCYLINDER_H

#include "CgBase/CgBaseTriangleMesh.h"

class CgCylinder : CgBaseTriangleMesh
{
public:
    CgCylinder();

    // CgBaseRenderableObject interface
    Cg::ObjectType getType() const;
    unsigned int getID() const;

    // CgBaseTriangleMesh interface
    const std::vector<glm::vec3> &getVertices() const;
    const std::vector<glm::vec3> &getVertexNormals() const;
    const std::vector<glm::vec3> &getVertexColors() const;
    const std::vector<glm::vec2> &getVertexTexCoords() const;
    const std::vector<unsigned int> &getTriangleIndices() const;
    const std::vector<glm::vec3> &getFaceNormals() const;
    const std::vector<glm::vec3> &getFaceColors() const;

private:

};

#endif // CGCYLINDER_H
