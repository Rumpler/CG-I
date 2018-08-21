#include "CgPolyline.h"

CgPolyline::CgPolyline(int id): CgBasePolyline(),
    m_type(Cg::Polyline),
    m_id(id)
{

}

CgPolyline::~CgPolyline()
{

}

void CgPolyline::addVertice(glm::vec3 vertice)
{
    vertices.push_back(vertice);
}

void CgPolyline::setColor(const glm::vec3 value)
{
    color = value;
}

void CgPolyline::setLineWidth(unsigned int value)
{
    lineWidth = value;
}

void CgPolyline::setRotationCurveExample1()
{
    vertices.clear();
    vertices.push_back(glm::vec3(0.18f, -0.31f, 0.0f));
    vertices.push_back(glm::vec3(0.2f, -0.3f, 0.0f));
    vertices.push_back(glm::vec3(0.4f, -0.2f, 0.0f));
    vertices.push_back(glm::vec3(0.4f, -0.1f, 0.0f));
    vertices.push_back(glm::vec3(0.3f, 0.0f, 0.0f));
    vertices.push_back(glm::vec3(0.1f, 0.1f, 0.0f));
    vertices.push_back(glm::vec3(0.4f, 0.2f, 0.0f));
    vertices.push_back(glm::vec3(0.3f, 0.3f, 0.0f));
    vertices.push_back(glm::vec3(0.29f, 0.31f, 0.0f));
}

void CgPolyline::setPawnContour()
{
    vertices.clear();
    vertices.push_back(glm::vec3(0.0f, 0.0f, 0.0f));
    vertices.push_back(glm::vec3(0.25f, 0.0f, 0.0f));
    vertices.push_back(glm::vec3(0.2f, 0.1f, 0.0f));
    vertices.push_back(glm::vec3(0.1f, 0.2f, 0.0f));
    vertices.push_back(glm::vec3(0.1f, 0.3f, 0.0f));
    vertices.push_back(glm::vec3(0.2f, 0.4f, 0.0f));
    vertices.push_back(glm::vec3(0.1f, 0.5f, 0.0f));
    vertices.push_back(glm::vec3(0.1f, 0.6f, 0.0f));
    vertices.push_back(glm::vec3(0.0f, 0.7f, 0.0f));
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

bool CgPolyline::getDisplay() const
{
    return display;
}

void CgPolyline::setDisplay(bool value)
{
    display = value;
}

