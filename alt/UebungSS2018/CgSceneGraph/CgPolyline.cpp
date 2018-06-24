#include "CgPolyline.h"

CgPolyline::CgPolyline(int id):
    m_type(Cg::Polyline),
    m_id(id),
    lineWidth(1)
{

}

CgPolyline::~CgPolyline()
{
    vertices.clear();
}

void CgPolyline::addVertice(glm::vec3 vertice)
{
    vertices.push_back(vertice);
}

Cg::ObjectType CgPolyline::getType() const
{
    return m_type;
}

unsigned int CgPolyline::getID() const
{
    return m_id;
}

const std::vector<glm::vec3> &CgPolyline::getVertices() const
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

void CgPolyline::setColor(const glm::vec3 value)
{
    color = value;
}

void CgPolyline::setLineWidth(unsigned int value)
{
    lineWidth = value;
}
