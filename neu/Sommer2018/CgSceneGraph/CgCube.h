#ifndef CGCUBE_H
#define CGCUBE_H

#include <vector>
#include <map>
#include <glm/glm.hpp>

#include "CgBase/CgBaseTriangleMesh.h"
#include "CgLine.h"
#include "CgTriangleMesh.h"
#include "CgBase/CgBaseRenderer.h"
#include "CgUtils/IdSingleton.h"

//@author Gerrit
class CgCube : public CgTriangleMesh
{

public:
    CgCube(int id);
    ~CgCube();

private:

    std::map<int, std::vector<glm::vec3>*> map_vertex_normals;

    void initFace(int p1, int p2, int p3);


};

#endif // CGCUBE_H
