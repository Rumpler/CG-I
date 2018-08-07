#ifndef CGTRIANGLES_H
#define CGTRIANGLES_H

#include <vector>
#include <map>
#include <glm/glm.hpp>
#include <string>
#include "CgBase/CgBaseTriangleMesh.h"
#include "CgTriangleMesh.h"


class CgTriangles : public CgTriangleMesh
{

public:
    CgTriangles(int id);
    ~CgTriangles();

    //inherited from CgBaseRenderableObject

    void init (std::vector<glm::vec3> arg_verts, std::vector<glm::vec3> arg_normals, std::vector<unsigned int> arg_triangle_indices);
    void init( std::string filename);
};

#endif // CGEXAMPLETRIANGLE_H
