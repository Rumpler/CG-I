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

/*!
 * \brief The CgCube class is a TriangleMesh with fix faces and normals
 */
class CgCube : public CgTriangleMesh
{

public:
    CgCube(int id);
    ~CgCube();
};

#endif // CGCUBE_H
