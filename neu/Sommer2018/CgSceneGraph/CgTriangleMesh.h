#ifndef CGTRIANGLEMESH_H
#define CGTRIANGLEMESH_H

#include "CgLine.h"

#include <CgBase/CgBaseTriangleMesh.h>

#include <CgUtils/IdSingleton.h>
#include <map>



class CgTriangleMesh : public CgBaseTriangleMesh
{
public:
    CgTriangleMesh(int id);
    ~CgTriangleMesh();

    // CgBaseRenderableObject interface
public:
    Cg::ObjectType getType() const;
    unsigned int getID() const;

    // CgBaseTriangleMesh interface
public:
    const std::vector<glm::vec3> &getVertices() const;
    const std::vector<glm::vec3> &getVertexNormals() const;
    const std::vector<glm::vec3> &getVertexColors() const;
    const std::vector<glm::vec2> &getVertexTexCoords() const;
    const std::vector<unsigned int> &getTriangleIndices() const;
    const std::vector<glm::vec3> &getFaceNormals() const;
    const std::vector<glm::vec3> &getFaceColors() const;


    const glm::vec3& getColor() const;
    void setColor(glm::vec3 color);

    std::vector<CgLine *>* getPolylineNormals();

    bool getDisplay() const;
    void setDisplay(bool value);

protected:
    IdSingleton* idGen;
    std::vector<CgLine*> polylineNormals;
    glm::vec3 color = glm::vec3(0.7f,0.0f,1.0f);
    bool display = false;

    std::vector<glm::vec3> m_vertices;
    std::vector<glm::vec3> m_vertex_normals;
    std::vector<glm::vec3> m_vertex_colors;
    std::vector<glm::vec2> m_tex_coords;

    std::vector<unsigned int>  m_triangle_indices;

    std::vector<glm::vec3> m_face_normals;
    std::vector<glm::vec3> m_face_colors;

    const Cg::ObjectType m_type;
    const unsigned int m_id;

    void pushPoly(glm::vec3 p1, glm::vec3 p2);

    std::map<int, std::vector<glm::vec3>*> map_vertex_normals;

    //needs m_vertices and m_triangle_indices to be filled previously
    void calculateNormals();

    void fillPolylineNormals();

};


#endif // CGTRIANGLEMESH_H
