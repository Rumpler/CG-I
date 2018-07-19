#ifndef CGEXAMPLETRIANGLE_H
#define CGEXAMPLETRIANGLE_H

#include <vector>
#include <glm/glm.hpp>
#include <string>
#include "CgBase/CgBaseTriangleMesh.h"
#include "CgTriangleMesh.h"


class CgExampleTriangle : public CgTriangleMesh
{

public:
    CgExampleTriangle(int id);
    ~CgExampleTriangle();

    //inherited from CgBaseRenderableObject

    void init (std::vector<glm::vec3> arg_verts, std::vector<glm::vec3> arg_normals, std::vector<unsigned int> arg_triangle_indices);
    void init( std::string filename);
};

#endif // CGEXAMPLETRIANGLE_H
