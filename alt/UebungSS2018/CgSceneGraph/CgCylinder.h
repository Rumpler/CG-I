#ifndef CGCYLINDER_H
#define CGCYLINDER_H

#include "CgBase/CgBaseTriangleMesh.h"

#include "CgPolyline.h"

class CgCylinder : public CgBaseTriangleMesh
{
public:
    CgCylinder(int id, int amountOfSegments, double height);
    ~CgCylinder();

    void makeCylinder(int amountOfSegments, double height);

    // CgBaseRenderableObject interface
    Cg::ObjectType getType() const;
    unsigned int getID() const;

    // CgBaseTriangleMesh interface
    const std::vector<glm::vec3> &getVertices() const;
    const std::vector<glm::vec3> &getVertexNormals() const;
    const std::vector<glm::vec3> &getVertexColors() const;
    const std::vector<glm::vec2> &getVertexTexCoords() const;
    const std::vector<unsigned int> &getTriangleIndices() const;
    const std::vector<glm::vec3> &getFaceNormals() const;
    const std::vector<glm::vec3> &getFaceColors() const;

private:
    std::vector<CgPolyline*> polylineNormals;

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

#endif // CGCYLINDER_H
