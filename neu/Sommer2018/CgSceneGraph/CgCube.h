#ifndef CGCUBE_H
#define CGCUBE_H

#include <vector>
#include <map>
#include <glm/glm.hpp>

#include "CgBase/CgBaseTriangleMesh.h"
#include "CgPolyline.h"
#include "CgTriangleMesh.h"
#include "CgBase/CgBaseRenderer.h"
#include "CgUtils/IdSingleton.h"

//@author Gerrit
class CgCube : public CgBaseTriangleMesh
{

public:
    CgCube(int id);
    ~CgCube();

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




    std::vector<CgPolyline *>* getPolylineNormals();



    const glm::vec3& getColor() const;
    void setColor(glm::vec3 color);

private:

    IdSingleton* idGen;

    void initFace(int p1, int p2, int p3);

    std::vector<CgPolyline*> polylineNormals;
    std::map<int, std::vector<glm::vec3>*> map_vertex_normals;

    glm::vec3 m_color = glm::vec3(0.7f,0.0f,1.0f);

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


inline Cg::ObjectType  CgCube::getType() const {return m_type;}
inline unsigned int CgCube::getID() const {return m_id;}

#endif // CGCUBE_H
