#include "CgTriangleMesh.h"

#include <CgUtils/CgUtils.h>

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

    map_vertex_normals.clear();
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



//needs m_vertices and m_triangle_indices to be filled previously
void CgTriangleMesh::computeNormals()
{
    m_vertex_normals.clear();
    m_face_normals.clear();

    //Initialize map
    for(int i = 0; i < (int) m_vertices.size(); i++){
        map_vertex_normals[i] = new std::vector<glm::vec3>;
    }

    int p1, p2, p3;
    for(int i = 0; i <= m_triangle_indices.size() - 3; i += 3){
        p1 = m_triangle_indices.at(i);
        p2 = m_triangle_indices.at(i+1);
        p3 = m_triangle_indices.at(i+2);

        //Calculate and push faceNormal
        glm::vec3 faceNormal = CgUtils::calcFaceNormal(m_vertices.at(p1),m_vertices.at(p2),m_vertices.at(p3));
        m_face_normals.push_back(faceNormal);

        //Map faceNormal to vertex
        map_vertex_normals.at(p1)->push_back(faceNormal);
        map_vertex_normals.at(p2)->push_back(faceNormal);
        map_vertex_normals.at(p3)->push_back(faceNormal);
    }


    //Calculating vertexNormals

    //For everey vertex
    for(int i = 0; i < (int) m_vertices.size(); i++){
        std::vector<glm::vec3>* temp = map_vertex_normals.at(i);
        glm::vec3 norm = glm::vec3(0.0,0.0,0.0);
        float normCounter = 0.0;

        //For everey normal per vertex
        for(int j = 0; j < (int) temp->size(); j++){
            norm = norm + temp->at(j);
            normCounter = normCounter + 1;
        }
        norm = norm / normCounter;
        norm = glm::normalize(norm);
        m_vertex_normals.push_back(norm);
    }
}

//needs m_triangle_indeces, m_vertices, m_vertex_normals and m_face_normals to be filled previously
void CgTriangleMesh::fillPolylineNormals()
{
    if(m_vertices.size() != m_vertex_normals.size() || m_triangle_indices.size() / 3 != m_face_normals.size()){return;} //check if presets are okay

    polylineNormals.clear();

    CgLine* poly;
    int p1, p2, p3;
    glm::vec3 focusPoint;

    //faceNormals
    for(int i = 0; i <= m_triangle_indices.size() - 3; i += 3){
        p1 = m_triangle_indices.at(i);
        p2 = m_triangle_indices.at(i + 1);
        p3 = m_triangle_indices.at(i + 2);
        poly = new CgLine(idGen->getNextId());
        focusPoint = CgUtils::calcFocusPointTriangle(m_vertices.at(p1),m_vertices.at(p2),m_vertices.at(p3));
        poly->addVertice(focusPoint);
        poly->addVertice(focusPoint + m_face_normals.at(i/3) * 0.1f);
        poly->setColor(glm::vec3(1.0f,1.0f,1.0f));
        polylineNormals.push_back(poly);
    }

    //vertexNormals
    for(int i = 0; i < m_vertices.size(); i++){
        poly = new CgLine(idGen->getNextId());
        poly->addVertice(m_vertices.at(i));
        poly->addVertice(m_vertices.at(i) + m_vertex_normals.at(i) * 0.1f);
        poly->setColor(glm::vec3(1.0f,1.0f,1.0f));
        polylineNormals.push_back(poly);
    }
}

void CgTriangleMesh::pushPoly(glm::vec3 p1, glm::vec3 p2)
{
//    CgLine* poly = new CgLine(idGen->getNextId());
//    poly->addVertice(p1);
//    poly->addVertice(p2);
//    poly->setColor(glm::vec3(1.0f,1.0f,1.0f));
//    polylineNormals.push_back(poly);
}

void CgTriangleMesh::initFace(int p1, int p2, int p3)
{
    m_triangle_indices.push_back(p1);
    m_triangle_indices.push_back(p2);
    m_triangle_indices.push_back(p3);
}
