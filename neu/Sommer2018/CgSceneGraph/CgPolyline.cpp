#include "CgPolyline.h"

CgPolyline::CgPolyline(int id):
    m_id(id),
    m_type(Cg::Polyline)
{

}

CgPolyline::~CgPolyline()
{
    vertices.clear();
}

Cg::ObjectType CgPolyline::getType() const
{
    return m_type;
}

unsigned int CgPolyline::getID() const
{
    return m_id;
}

const std::vector<glm::vec3>& CgPolyline::getVertices() const
{
    return vertices;
}

glm::vec3 CgPolyline::getColor() const
{
    return color;
}

unsigned int CgPolyline::getLineWidth() const
{
    return lineWidth;
}
