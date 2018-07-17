#ifndef CGPOLYLINE_H
#define CGPOLYLINE_H

#include "CgBase/CgBasePolyline.h"
#include <iostream>


class CgPolyline : public CgBasePolyline
{
public:
    CgPolyline(int id);
    ~CgPolyline();
    void addVertice(glm::vec3 vertice);


    void sdForPointScheme();
    void sdChaikins();
    void sdLaneRiesenfeld();


    // CgBaseRenderableObject interface
    Cg::ObjectType getType() const;
    unsigned int getID() const;

    // CgBasePolyline interface
    const std::vector<glm::vec3> &getVertices() const;
    glm::vec3 getColor() const;
    unsigned int getLineWidth() const;

    void setColor(const glm::vec3 value);

    void setLineWidth(unsigned int value);

    void setRotationCurveExample1();

private:
    const Cg::ObjectType m_type;
    const unsigned int m_id;

    std::vector<glm::vec3> vertices;
    glm::vec3 color;
    unsigned int lineWidth;

    void printVertices();


};

#endif // CGPOLYLINE_H
