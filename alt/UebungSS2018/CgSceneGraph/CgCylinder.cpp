#include "CgCylinder.h"

CgCylinder::CgCylinder(int id):
    m_type(Cg::TriangleMesh),
    m_id(id)
{

}

Cg::ObjectType CgCylinder::getType() const
{
    return m_type;
}

unsigned int CgCylinder::getID() const
{
    return m_id;
}

const std::vector<glm::vec3> &CgCylinder::getVertices() const
{
    return m_vertices;
}

const std::vector<glm::vec3> &CgCylinder::getVertexNormals() const
{
    return m_vertex_normals;
}

const std::vector<glm::vec3> &CgCylinder::getVertexColors() const
{
    return m_vertex_colors;
}

const std::vector<glm::vec2> &CgCylinder::getVertexTexCoords() const
{
    return m_tex_coords;
}

const std::vector<unsigned int> &CgCylinder::getTriangleIndices() const
{
    return m_triangle_indices;
}

const std::vector<glm::vec3> &CgCylinder::getFaceNormals() const
{
    return m_face_normals;
}

const std::vector<glm::vec3> &CgCylinder::getFaceColors() const
{
    return m_face_colors;
}
