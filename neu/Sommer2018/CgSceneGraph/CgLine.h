#ifndef CGLINE_H
#define CGLINE_H

#include "CgBase/CgBasePolyline.h"
#include <iostream>
#include "CgPolyline.h"



class CgLine : public CgPolyline
{
public:
    CgLine(int id);
    CgLine(int id, glm::vec3 p1, glm::vec3 p2);
    ~CgLine();

    void sdForPointScheme();
    void sdChaikins();
    void sdLaneRiesenfeld();

};

#endif // CGPOLYLINE_H
