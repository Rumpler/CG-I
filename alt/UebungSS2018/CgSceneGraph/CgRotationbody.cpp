#include "CgRotationbody.h"

CgRotationbody::CgRotationbody(int id, CgPolyline* contourCurve):
    m_type(Cg::TriangleMesh),
    m_id(id),
    contourCurve(contourCurve)
{

}

Cg::ObjectType CgRotationbody::getType() const
{
    return m_type;
}

unsigned int CgRotationbody::getID() const
{
    return m_id;
}

const std::vector<glm::vec3> &CgRotationbody::getVertices() const
{
    return m_vertices;
}

const std::vector<glm::vec3> &CgRotationbody::getVertexNormals() const
{
    return m_vertex_normals;
}

const std::vector<glm::vec3> &CgRotationbody::getVertexColors() const
{
    return m_vertex_colors;
}

const std::vector<glm::vec2> &CgRotationbody::getVertexTexCoords() const
{
    return m_tex_coords;
}

const std::vector<unsigned int> &CgRotationbody::getTriangleIndices() const
{
    return m_triangle_indices;
}

const std::vector<glm::vec3> &CgRotationbody::getFaceNormals() const
{
    return m_face_normals;
}

const std::vector<glm::vec3> &CgRotationbody::getFaceColors() const
{
    return m_face_colors;
}
