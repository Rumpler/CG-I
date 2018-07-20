#include "CgCylinder.h"

CgCylinder::CgCylinder(int id): CgTriangleMesh(id)
{
    m_vertices.push_back(glm::vec3(1.0f,0.0f,0.0f));
    m_vertices.push_back(glm::vec3(0.0f,1.0f,0.0f));
    m_vertices.push_back(glm::vec3(0.0f,0.0f,1.0f));

    m_triangle_indices.push_back(0);
    m_triangle_indices.push_back(1);
    m_triangle_indices.push_back(2);
}
