#ifndef CGCYLINDER_H
#define CGCYLINDER_H

#include "CgTriangleMesh.h"


/*!
 * \brief The CgCylinder class is a special TriangleMesh which is defined by the amount of segments ant the height it should have.
 *
 * It uses the special ability of rotation to compute the normals and faces instead of using the abilitys of TriangleMesh
 */
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
