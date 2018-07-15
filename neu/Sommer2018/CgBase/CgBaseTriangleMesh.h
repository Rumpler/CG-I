#ifndef CGBASETRIANGLEMESH_H
#define CGBASETRIANGLEMESH_H


#include <vector>
#include <glm/glm.hpp>
#include "CgBase/CgBaseRenderableObject.h"

class CgBaseTriangleMesh : public CgBaseRenderableObject
{
public:

    virtual ~CgBaseTriangleMesh(){};


    virtual const std::vector<glm::vec3>& getVertices()     const =0;
    virtual const std::vector<glm::vec3>& getVertexNormals() const =0;
    virtual const std::vector<glm::vec3>& getVertexColors() const =0;

    virtual const std::vector<glm::vec2>& getVertexTexCoords() const =0;

    // ein Dreieck hat immer 3 Indices, also ist die Index-Liste 3 mal so lang wie die Anzahl der Dreiecke
    virtual const std::vector<unsigned int>& getTriangleIndices() const =0;

    // Es gibt so viele Face-Normalen wie Polygone/Dreiecke, da ein Face als planar angenommen wird und daher genau eine Normale hat.
    virtual const std::vector<glm::vec3>& getFaceNormals() const =0;

    // Falls eine Farbe pro Polygon spezifiziert ist, so ist es einfarbig in genau dieser Farbe, also auch #Farben=#Faces
    virtual const std::vector<glm::vec3>& getFaceColors() const =0;

};



#endif // CGBASETRIANGLEMESH_H
