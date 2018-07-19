#ifndef CGPOLYLINE_H
#define CGPOLYLINE_H

#include <CgBase/CgBasePolyline.h>



class CgPolyline : public CgBasePolyline
{
public:
    CgPolyline(int id);
    ~CgPolyline();

    // CgBaseRenderableObject interface
public:
    Cg::ObjectType getType() const;
    unsigned int getID() const;

    // CgBasePolyline interface
public:
    const std::vector<glm::vec3> &getVertices() const;
    glm::vec3 getColor() const;
    unsigned int getLineWidth() const;


private:
    const Cg::ObjectType m_type;
    const unsigned int m_id;

    std::vector<glm::vec3> vertices;

    glm::vec3 color = glm::vec3(0.7f,0.0f,1.0f);
    unsigned int lineWidth;

};

#endif // CGPOLYLINE_H
