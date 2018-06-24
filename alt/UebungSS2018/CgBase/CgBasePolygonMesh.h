#ifndef CGBASEPOLYGONMESH_H
#define CGBASEPOLYGONMESH_H


#include <vector>
#include <glm/glm.hpp>
#include "CgBase/CgBaseRenderableObject.h"

class CgBasePolygonMesh : public CgBaseRenderableObject
{
public:
    CgBasePolygonMesh();


    virtual const std::vector<glm::vec3>& getVertices()     const =0;
    virtual const std::vector<glm::vec3>& getVertexNormals() const =0;
    virtual const std::vector<glm::vec3>& getVertexColors() const =0;

    virtual const std::vector<glm::vec2>& getVertexTexCoords() const =0;

    // ein Polygon hat beliebige Anzahl Indices, also ist die Index-Liste eine Liste aus je einer Liste von Indices pro Polygon
    virtual const std::vector<std::vector<unsigned int> >& getPolygonIndices() const =0;

    // Es gibt so viele Face-Normalen wie Polygone/Dreiecke, da ein Face als planar angenommen wird und daher genau eine Normale hat.
    virtual const std::vector<glm::vec3>& getFaceNormals() const =0;

    // Falls eine Farbe pro Polygon spezifiziert ist, so ist es einfarbig in genau diese Farbe, also auch #Farben=#Faces
    virtual const std::vector<glm::vec3>& getFaceColors() const =0;


};

#endif // CGBASEPOLYGONMESH_H
