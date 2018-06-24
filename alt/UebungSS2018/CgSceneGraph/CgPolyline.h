#ifndef CGPOLYLINE_H
#define CGPOLYLINE_H

#include "CgBase/CgBasePolyline.h"


class CgPolyline : public CgBasePolyline
{
public:
    CgPolyline(int id);
    ~CgPolyline();
    void addVertice(glm::vec3 vertice);




    // CgBaseRenderableObject interface
    Cg::ObjectType getType() const;
    unsigned int getID() const;

    // CgBasePolyline interface
    const std::vector<glm::vec3> &getVertices() const;
    glm::vec3 getColor() const;
    unsigned int getLineWidth() const;

    void setColor(const glm::vec3 value);

    void setLineWidth(unsigned int value);

private:
    const Cg::ObjectType m_type;
    const unsigned int m_id;

    std::vector<glm::vec3> vertices;
    glm::vec3 color;
    unsigned int lineWidth;


};

#endif // CGPOLYLINE_H
