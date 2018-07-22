#include "CgTriangleMesh.h"

CgTriangleMesh::CgTriangleMesh(int id) : CgBaseTriangleMesh(),
    m_type(Cg::TriangleMesh),
    m_id(id)
{
    idGen = IdSingleton::instance();
}

CgTriangleMesh::~CgTriangleMesh()
{
    m_vertices.clear();
    m_vertex_normals.clear();
    m_vertex_colors.clear();
    m_tex_coords.clear();
    m_triangle_indices.clear();
    m_face_normals.clear();
    m_face_colors.clear();

    polylineNormals.clear();
}

const glm::vec3 &CgTriangleMesh::getColor() const
{
    return color;
}

void CgTriangleMesh::setColor(glm::vec3 color)
{
    this->color = color;
}

std::vector<CgLine *> *CgTriangleMesh::getPolylineNormals()
{

    //TODO calculating CgLines on demand instead of pushing them through whole progress (mayby later)
//    std::vector<CgLine*>* lineNormals = new std::vector<CgLine*>;
//    CgLine* line;
//    for(int i = 0; i < m_vertices.size(); i++){
//        line = new CgLine(idGen->getNextId(), m_vertices.at(i), m_vertices.at(i) + m_vertex_normals.at(i));
//        //TODO set color etc...
//        lineNormals->push_back(line);
//    }

    return &polylineNormals;
}

Cg::ObjectType CgTriangleMesh::getType() const
{
    return m_type;
}

unsigned int CgTriangleMesh::getID() const
{
    return m_id;
}

const std::vector<glm::vec3> &CgTriangleMesh::getVertices() const
{
    return m_vertices;
}

const std::vector<glm::vec3> &CgTriangleMesh::getVertexNormals() const
{
    return m_vertex_normals;
}

const std::vector<glm::vec3> &CgTriangleMesh::getVertexColors() const
{
    return m_vertex_colors;
}

const std::vector<glm::vec2> &CgTriangleMesh::getVertexTexCoords() const
{
    return m_tex_coords;
}

const std::vector<unsigned int> &CgTriangleMesh::getTriangleIndices() const
{
    return m_triangle_indices;
}

const std::vector<glm::vec3> &CgTriangleMesh::getFaceNormals() const
{
    return m_face_normals;
}

const std::vector<glm::vec3> &CgTriangleMesh::getFaceColors() const
{
    return m_face_colors;
}

bool CgTriangleMesh::getDisplay() const
{
    return display;
}

void CgTriangleMesh::setDisplay(bool value)
{
    display = value;
}
