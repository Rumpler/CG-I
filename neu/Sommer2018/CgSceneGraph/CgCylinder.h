#ifndef CGCYLINDER_H
#define CGCYLINDER_H

#include "CgTriangleMesh.h"


//TODO fill m_face_normals and m_vertex_normals (polyline normals done)
class CgCylinder : public CgTriangleMesh
{
public:
    CgCylinder(int id, int amountOfSegments, double height, double radius);

    void makeCylinder(int amountOfSegments, double height, double radius);

private:
    int amountOfSegments;
    double height;
};

#endif // CGCYLINDER_H
