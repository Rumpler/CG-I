#ifndef CGTRIANGLEMESH_H
#define CGTRIANGLEMESH_H

#include "CgPolyline.h"

#include <CgBase/CgBaseTriangleMesh.h>

#include <CgUtils/IdSingleton.h>



class CgTriangleMesh : public virtual CgBaseTriangleMesh
{
public:
    CgTriangleMesh(int id);
    ~CgTriangleMesh();

    const glm::vec3& getColor() const;
    void setColor(glm::vec3 color);

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



protected:
    IdSingleton* idGen;
    std::vector<CgPolyline*> polylineNormals;
    glm::vec3 color = glm::vec3(0.7f,0.0f,1.0f);

    std::vector<glm::vec3> m_vertices;
    std::vector<glm::vec3> m_vertex_normals;
    std::vector<glm::vec3> m_vertex_colors;
    std::vector<glm::vec2> m_tex_coords;

    std::vector<unsigned int>  m_triangle_indices;

    std::vector<glm::vec3> m_face_normals;
    std::vector<glm::vec3> m_face_colors;

    const Cg::ObjectType m_type;
    const unsigned int m_id;

};


#endif // CGTRIANGLEMESH_H
