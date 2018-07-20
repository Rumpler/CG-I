#ifndef CGLINE_H
#define CGLINE_H

#include "CgBase/CgBasePolyline.h"
#include <iostream>
#include "CgPolyline.h"



class CgLine : public CgPolyline
{
public:
    CgLine(int id);
    ~CgLine();

    void sdForPointScheme();
    void sdChaikins();
    void sdLaneRiesenfeld();

};

#endif // CGPOLYLINE_H
