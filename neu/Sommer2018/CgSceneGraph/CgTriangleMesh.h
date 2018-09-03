#ifndef CGTRIANGLEMESH_H
#define CGTRIANGLEMESH_H

#include "CgLine.h"

#include <CgBase/CgBaseTriangleMesh.h>

#include <CgUtils/IdSingleton.h>
#include <map>


/*!
 * \brief The CgTriangleMesh class
 *
 * test
 */
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

    float getShininess() const;
    void setShininess(float value);

protected:
    IdSingleton* idGen;     //!< Detailed description
    std::vector<CgLine*> polylineNormals;
    glm::vec3 color = glm::vec3(0.7f,0.0f,1.0f);
    bool display = false;

    //DON
    float shininess;

    std::vector<glm::vec3> m_vertices;
    std::vector<glm::vec3> m_vertex_normals;
    std::vector<glm::vec3> m_vertex_colors;
    std::vector<glm::vec2> m_tex_coords;

    std::vector<unsigned int>  m_triangle_indices;

    std::vector<glm::vec3> m_face_normals;
    std::vector<glm::vec3> m_face_colors;

    const Cg::ObjectType m_type;
    const unsigned int m_id;

    //depricated (replaced by fillPolylineNormals)
    void pushPoly(glm::vec3 p1, glm::vec3 p2);

    std::map<int, std::vector<glm::vec3>*> map_vertex_normals;

    //needs m_vertices and m_triangle_indices to be filled previously
    void computeNormals();

    //needs m_triangle_indeces, m_vertices, m_vertex_normals and m_face_normals to be filled previously
    void fillPolylineNormals();

    //push 3 int into m_triangle_indices
    void initFace(int p1, int p2, int p3);

};


#endif // CGTRIANGLEMESH_H
