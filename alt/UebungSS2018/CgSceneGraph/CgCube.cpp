#include "CgCube.h"
#include "CgBase/CgEnums.h"
#include <iostream>
#include <map>



CgCube::CgCube(int id):
m_type(Cg::TriangleMesh),
m_id(id)
{
    idGen = IdSingleton::instance();

    m_vertices.push_back(glm::vec3(.5,.5,.5));      //0
    m_vertices.push_back(glm::vec3(-.5,.5,.5));     //1
    m_vertices.push_back(glm::vec3(.5,-.5,.5));     //2
    m_vertices.push_back(glm::vec3(-.5,-.5,.5));    //3
    m_vertices.push_back(glm::vec3(.5,.5,-.5));     //4
    m_vertices.push_back(glm::vec3(-.5,.5,-.5));    //5
    m_vertices.push_back(glm::vec3(.5,-.5,-.5));    //6
    m_vertices.push_back(glm::vec3(-.5,-.5,-.5));   //7


    //Initialize map
    for(int i = 0; i < (int) m_vertices.size(); i++){
        map_vertex_normals[i] = new std::vector<glm::vec3>;
    }

    initFace(7,6,4);
    initFace(4,5,7);
    initFace(6,2,0);
    initFace(0,4,6);
    initFace(2,3,1);
    initFace(1,0,2);
    initFace(3,7,5);
    initFace(5,1,3);
    initFace(1,5,4);
    initFace(4,0,1);
    initFace(2,6,7);
    initFace(7,3,2);

    //Calculating vertexNormals


    CgPolyline* poly;

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
        glm::normalize(norm);
        m_vertex_normals.push_back(norm);

        //Push polyline for rendering
        poly = new CgPolyline(idGen->getNextId());
        poly->addVertice(m_vertices.at(i));
        poly->addVertice(m_vertices.at(i) + (norm * 0.1f));
        polylineNormals.push_back(poly);
    }






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
    polylineNormals.clear();
    map_vertex_normals.clear();
}

//Initializes face, pushes faceNormal, calculates focusPoint, pushes polyline for rendering and map faceNormal to vertex
void CgCube::initFace(int p1, int p2, int p3)
{


    //Init face
    m_triangle_indices.push_back(p1);
    m_triangle_indices.push_back(p2);
    m_triangle_indices.push_back(p3);

    //Calculate and push faceNormal
    glm::vec3 u = m_vertices.at(p2) - m_vertices.at(p1);
    glm::vec3 v = m_vertices.at(p3) - m_vertices.at(p1);
    glm::vec3 faceNormal = glm::cross(v,u);
    glm::normalize(faceNormal);

    m_face_normals.push_back(faceNormal);

    //Map faceNormal to vertex
    map_vertex_normals.at(p1)->push_back(faceNormal);
    map_vertex_normals.at(p2)->push_back(faceNormal);
    map_vertex_normals.at(p3)->push_back(faceNormal);

    //Calculate focusPoint
    glm::vec3 focusPoint = glm::vec3((m_vertices.at(p1).x + m_vertices.at(p2).x + m_vertices.at(p3).x) / 3.0,
                                     (m_vertices.at(p1).y + m_vertices.at(p2).y + m_vertices.at(p3).y) / 3.0,
                                     (m_vertices.at(p1).z + m_vertices.at(p2).z + m_vertices.at(p3).z) / 3.0);

    //Push polyline for rendering
    CgPolyline* poly = new CgPolyline(idGen->getNextId());
    poly->addVertice(focusPoint);
    poly->addVertice(focusPoint + (faceNormal * 0.1f));
    polylineNormals.push_back(poly);
}


std::vector<CgPolyline *>& CgCube::getPolylineNormals()
{
    return polylineNormals;
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


