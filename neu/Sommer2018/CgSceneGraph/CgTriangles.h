#ifndef CGEXAMPLETRIANGLE_H
#define CGEXAMPLETRIANGLE_H

#include <vector>
#include <glm/glm.hpp>

#include "CgBase/CgBaseTriangleMesh.h"



class CgTriangles : public CgBaseTriangleMesh
{

public:
    CgTriangles(int id);
    CgTriangles(int id, std::vector<glm::vec3> *pos, std::vector<unsigned int> *index);
    ~CgTriangles();

    //inherited from CgBaseRenderableObject
    Cg::ObjectType getType() const;
    unsigned int getID() const;

    //inherited from CgBaseTriangleMesh
    const std::vector<glm::vec3>& getVertices() const;
    const std::vector<glm::vec3>& getVertexNormals() const;
    const std::vector<glm::vec3>& getVertexColors() const;
    const std::vector<glm::vec2>& getVertexTexCoords() const;

    const std::vector<unsigned int>& getTriangleIndices() const;

    const std::vector<glm::vec3>& getFaceNormals() const;
    const std::vector<glm::vec3>& getFaceColors() const;




    const glm::vec3 getColor() const;
    void setColor(const glm::vec3 &color);

private:

    glm::vec3 m_color = glm::vec3(0.7f,0.0f,0.15f);

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


inline Cg::ObjectType  CgTriangles::getType() const {return m_type;}
inline unsigned int CgTriangles::getID() const {return m_id;}

#endif // CGEXAMPLETRIANGLE_H
