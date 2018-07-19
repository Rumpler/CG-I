#include "CgTriangles.h"
#include "CgBase/CgEnums.h"


CgTriangles::CgTriangles(int id):
    m_type(Cg::TriangleMesh),
    m_id(id)
{

}

CgTriangles::CgTriangles(int id, std::vector<glm::vec3> *pos, std::vector<unsigned int> *index):
m_type(Cg::TriangleMesh),
m_id(id)
{
    for(glm::vec3 vertice : *pos){
        m_vertices.push_back(vertice);
    }
    for(unsigned int i : *index){
        m_triangle_indices.push_back(i);
    }


}


CgTriangles::~CgTriangles()
{
    m_vertices.clear();
    m_vertex_normals.clear();
    m_vertex_colors.clear();
    m_tex_coords.clear();
    m_triangle_indices.clear();
    m_face_normals.clear();
    m_face_colors.clear();
}


const std::vector<glm::vec3>& CgTriangles::getVertices() const
{
    return m_vertices;
}

const std::vector<glm::vec3>& CgTriangles::getVertexNormals() const
{
    return m_vertex_normals;
}

const std::vector<glm::vec3>& CgTriangles::getVertexColors() const
{
     return m_vertex_colors;
}

const std::vector<glm::vec2>& CgTriangles:: getVertexTexCoords() const
{
    return m_tex_coords;
}

const std::vector<unsigned int>& CgTriangles::getTriangleIndices() const
{
    return m_triangle_indices;
}

const std::vector<glm::vec3>& CgTriangles::getFaceNormals() const
{
    return m_face_normals;
}

const std::vector<glm::vec3>& CgTriangles::getFaceColors() const
{
    return m_face_colors;
}

const glm::vec3 CgTriangles::getColor() const
{
    return m_color;
}

void CgTriangles::setColor(const glm::vec3 &color)
{
    m_color = color;
}
