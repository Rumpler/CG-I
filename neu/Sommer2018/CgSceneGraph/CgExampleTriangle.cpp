#include "CgExampleTriangle.h"
#include "CgBase/CgEnums.h"
#include "CgUtils/ObjLoader.h"


CgExampleTriangle::CgExampleTriangle(int id):
m_type(Cg::TriangleMesh),
m_id(id)
{

    m_vertices.push_back(glm::vec3(-0.5,0.0,0.0));
    m_vertices.push_back(glm::vec3(0.0,-0.5,0.0));
    m_vertices.push_back(glm::vec3(0.0,0.5,0.0));
    m_vertices.push_back(glm::vec3(0.5,0.0,0.0));

    m_triangle_indices.push_back(0);
    m_triangle_indices.push_back(1);
    m_triangle_indices.push_back(2);
    m_triangle_indices.push_back(2);
    m_triangle_indices.push_back(1);
    m_triangle_indices.push_back(3);

    m_vertex_normals.push_back(glm::vec3(0.0,0.0,1.0));
    m_vertex_normals.push_back(glm::vec3(0.0,0.0,1.0));
    m_vertex_normals.push_back(glm::vec3(0.0,0.0,1.0));
    m_vertex_normals.push_back(glm::vec3(0.0,0.0,1.0));

}



CgExampleTriangle::~CgExampleTriangle()
{
    m_vertices.clear();
    m_vertex_normals.clear();
    m_vertex_colors.clear();
    m_tex_coords.clear();
    m_triangle_indices.clear();
    m_face_normals.clear();
    m_face_colors.clear();
}

void CgExampleTriangle::init( std::vector<glm::vec3> arg_verts,  std::vector<glm::vec3> arg_normals, std::vector<unsigned int> arg_triangle_indices)
{
    m_vertices.clear();
    m_vertex_normals.clear();
    m_triangle_indices.clear();
    m_vertices=arg_verts;
    m_vertex_normals=arg_normals;
    m_triangle_indices=arg_triangle_indices;
}

void CgExampleTriangle::init( std::string filename)
{
    m_vertices.clear();
    m_vertex_normals.clear();
    m_triangle_indices.clear();

    ObjLoader loader;
    loader.load(filename);

    loader.getPositionData(m_vertices);
    loader.getNormalData(m_vertex_normals);
    loader.getFaceIndexData(m_triangle_indices);
}

const std::vector<glm::vec3>& CgExampleTriangle::getVertices() const
{
    return m_vertices;
}

const std::vector<glm::vec3>& CgExampleTriangle::getVertexNormals() const
{
    return m_vertex_normals;
}

const std::vector<glm::vec3>& CgExampleTriangle::getVertexColors() const
{
     return m_vertex_colors;
}

const std::vector<glm::vec2>& CgExampleTriangle:: getVertexTexCoords() const
{
    return m_tex_coords;
}

const std::vector<unsigned int>& CgExampleTriangle::getTriangleIndices() const
{
    return m_triangle_indices;
}

const std::vector<glm::vec3>& CgExampleTriangle::getFaceNormals() const
{
    return m_face_normals;
}

const std::vector<glm::vec3>& CgExampleTriangle::getFaceColors() const
{
    return m_face_colors;
}

const glm::vec3 CgExampleTriangle::getColor() const
{
    return color;
}

void CgExampleTriangle::setColor(const glm::vec3 &value)
{
    color = value;
}
