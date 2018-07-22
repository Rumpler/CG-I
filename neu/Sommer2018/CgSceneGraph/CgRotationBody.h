#ifndef CGROTATIONBODY_H
#define CGROTATIONBODY_H

#include "CgLine.h"
#include "CgTriangleMesh.h"

#include <CgBase/CgBaseTriangleMesh.h>

#include <CgUtils/IdSingleton.h>
#include <CgUtils/CgUtils.h>



class CgRotationBody: public CgTriangleMesh
{
public:
    CgRotationBody(int id, CgLine* contourCurve, int amountOfSegments);

private:
    CgLine* contourCurve;
    int amountOfSegments;
};

#endif // CGROTATIONBODY_H
