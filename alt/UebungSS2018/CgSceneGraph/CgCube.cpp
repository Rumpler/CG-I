#include "CgCube.h"
#include "CgBase/CgEnums.h"


CgCube::CgCube(int id):
m_type(Cg::TriangleMesh),
m_id(id)
{

    m_vertices.push_back(glm::vec3(.5,.5,.5));      //0
    m_vertices.push_back(glm::vec3(-.5,.5,.5));     //1
    m_vertices.push_back(glm::vec3(.5,-.5,.5));     //2
    m_vertices.push_back(glm::vec3(-.5,-.5,.5));    //3
    m_vertices.push_back(glm::vec3(.5,.5,-.5));     //4
    m_vertices.push_back(glm::vec3(-.5,.5,-.5));    //5
    m_vertices.push_back(glm::vec3(.5,-.5,-.5));    //6
    m_vertices.push_back(glm::vec3(-.5,-.5,-.5));   //7


    m_triangle_indices.push_back(7);
    m_triangle_indices.push_back(6);
    m_triangle_indices.push_back(4);

    m_triangle_indices.push_back(4);
    m_triangle_indices.push_back(5);
    m_triangle_indices.push_back(7);

    m_triangle_indices.push_back(6);
    m_triangle_indices.push_back(2);
    m_triangle_indices.push_back(0);

    m_triangle_indices.push_back(0);
    m_triangle_indices.push_back(4);
    m_triangle_indices.push_back(6);

    m_triangle_indices.push_back(2);
    m_triangle_indices.push_back(3);
    m_triangle_indices.push_back(1);

    m_triangle_indices.push_back(1);
    m_triangle_indices.push_back(0);
    m_triangle_indices.push_back(2);

    m_triangle_indices.push_back(3);
    m_triangle_indices.push_back(7);
    m_triangle_indices.push_back(5);

    m_triangle_indices.push_back(5);
    m_triangle_indices.push_back(1);
    m_triangle_indices.push_back(3);

    m_triangle_indices.push_back(1);
    m_triangle_indices.push_back(5);
    m_triangle_indices.push_back(4);

    m_triangle_indices.push_back(4);
    m_triangle_indices.push_back(0);
    m_triangle_indices.push_back(1);

    m_triangle_indices.push_back(2);
    m_triangle_indices.push_back(6);
    m_triangle_indices.push_back(7);

    m_triangle_indices.push_back(7);
    m_triangle_indices.push_back(3);
    m_triangle_indices.push_back(2);

}


CgCube::~CgCube()
{
    m_vertices.clear();
    m_vertex_normals.clear();
    m_vertex_colors.clear();
    m_tex_coords.clear();
    m_triangle_indices.clear();
    m_face_normals.clear();
    m_face_colors.clear();
}


const std::vector<glm::vec3>& CgCube::getVertices() const
{
    return m_vertices;
}

const std::vector<glm::vec3>& CgCube::getVertexNormals() const
{
    return m_vertex_normals;
}

const std::vector<glm::vec3>& CgCube::getVertexColors() const
{
     return m_vertex_colors;
}

const std::vector<glm::vec2>& CgCube:: getVertexTexCoords() const
{
    return m_tex_coords;
}

const std::vector<unsigned int>& CgCube::getTriangleIndices() const
{
    return m_triangle_indices;
}

const std::vector<glm::vec3>& CgCube::getFaceNormals() const
{
    return m_face_normals;
}

const std::vector<glm::vec3>& CgCube::getFaceColors() const
{
    return m_face_colors;
}
