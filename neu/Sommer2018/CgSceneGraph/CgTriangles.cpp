#include "CgTriangles.h"
#include "CgBase/CgEnums.h"
#include "CgUtils/ObjLoader.h"

#include <CgUtils/CgUtils.h>


CgTriangles::CgTriangles(int id) : CgTriangleMesh(id)
{
}



CgTriangles::~CgTriangles()
{
}

void CgTriangles::init( std::vector<glm::vec3> arg_verts,  std::vector<glm::vec3> arg_normals, std::vector<unsigned int> arg_triangle_indices)
{
    m_vertices.clear();
    m_vertex_normals.clear();
    m_triangle_indices.clear();
    m_vertices=arg_verts;
    m_vertex_normals=arg_normals;
    m_triangle_indices=arg_triangle_indices;
}

void CgTriangles::init(std::string filename)
{
    m_vertices.clear();
    m_vertex_normals.clear();
    m_triangle_indices.clear();

    ObjLoader loader;
    loader.load(filename);

    loader.getPositionData(m_vertices);
    //loader.getNormalData(m_vertex_normals);
    loader.getFaceIndexData(m_triangle_indices);
    calculateNormals();
}





