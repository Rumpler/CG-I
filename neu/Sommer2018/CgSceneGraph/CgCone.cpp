#include "CgCone.h"
#include <math.h>
#include <iostream>
#include "CgUtils/CgUtils.h"

CgCone::CgCone(int id, int amountOfSegments, double height):
    m_type(Cg::TriangleMesh),
    m_id(id)
{
    //Test if enough segments are given
    if(amountOfSegments < 2){
        std::cout << "Too few segments" << std::endl;
        //Exception
        return;
    }

    idGen = IdSingleton::instance();

    //Initial values
    glm::vec3 initPoint = glm::vec3(0.2f, 0.0f, 0.0f);              //Init Point
    double angleOfRotation = 360.0 / amountOfSegments;
    angleOfRotation = (2.0 * M_PI / 360.0) * angleOfRotation;     //Translate in rad

    //First 3 points
    m_vertices.push_back(glm::vec3(0.0f, (float)height, 0.0f));     //Top of cylinder
    m_vertices.push_back((glm::vec3(0.0f, 0.0f, 0.0f)));            //Bottom center of cylinder
    m_vertices.push_back(initPoint);                                //First point

    //Indices
    int top = 0;
    int bottom = 1;
    int first = 2;
    int last = 2;

    //Vars for loop
    double currentAngle;
    glm::vec3 focusPointTop;
    glm::vec3 focusPointBottom;
    glm::vec3 faceNormalTop;
    glm::vec3 faceNormalBottom;
    glm::vec3 newFocusPointTop;
    glm::vec3 newFocusPointBottom;
    glm::vec3 newFaceNormalTopPoint;
    glm::vec3 newFaceNormalBottomPoint;

    //Calculate next point, next normal etc.
    //First loop normal calculation and then with rotation of first calculation
    for(int i = 0; i < amountOfSegments; i++){
        currentAngle = angleOfRotation * (i + 1);

        //Calculate new x and y and push new point
        m_vertices.push_back(CgU::rotatePointYAxis(currentAngle, initPoint));

        //Create 2 new faces
        if(i < amountOfSegments -1){            //Any loop but the last
            createFace(top, last, last +1);
            createFace(bottom, last +1, last);
        }else{                                  //Last loop
            createFace(top,last,first);
            createFace(bottom,last,first);
        }


        //Only in first loop (calculate first normals for first faces)
        if(i == 0){

            /* ################# Calculate 2 faceNormals for first top and bottom face ################# */

                //Calculate focusPoints
                focusPointTop = CgU::calcFocusPointTriangle(m_vertices.at(top), m_vertices.at(last), m_vertices.at(last + 1));
                focusPointBottom = CgU::calcFocusPointTriangle(m_vertices.at(bottom), m_vertices.at(last + 1), m_vertices.at(last));

                //Calculate and push faceNormals
                faceNormalTop = CgU::calcFaceNormal(m_vertices.at(last), m_vertices.at(top), m_vertices.at(last + 1));
                m_face_normals.push_back(faceNormalTop);
                faceNormalBottom = CgU::calcFaceNormal(m_vertices.at(last + 1), m_vertices.at(bottom), m_vertices.at(last));
                m_face_normals.push_back(faceNormalBottom);

                //Push polylines
                pushPoly(focusPointTop, focusPointTop + faceNormalTop * 0.1f);
                pushPoly(focusPointBottom, focusPointBottom + faceNormalBottom * 0.1f);

            /* ################# END ################# */

            /* ################# Calculate next step faceNormals for bottom and top to get in order (with rotation) ################# */

                //Rotate focusPoint
                newFocusPointTop = CgU::rotatePointYAxis(currentAngle, focusPointTop);
                newFocusPointBottom = CgU::rotatePointYAxis(currentAngle, focusPointBottom);

                //Rotate normal endpoint
                newFaceNormalTopPoint = focusPointTop + faceNormalTop * 0.1f;
                newFaceNormalTopPoint = CgU::rotatePointYAxis(currentAngle, newFaceNormalTopPoint);
                newFaceNormalBottomPoint = focusPointBottom + faceNormalBottom * 0.1f;
                newFaceNormalBottomPoint = CgU::rotatePointYAxis(currentAngle, newFaceNormalBottomPoint);

                //Push polyline
                pushPoly(newFocusPointTop, newFaceNormalTopPoint);
                pushPoly(newFocusPointBottom, newFaceNormalBottomPoint);

            /* ################# END ################# */


        //Calculate faceNormals with rotation routine in any loop but the first and last
        }else if(i > 0 && i < amountOfSegments - 1){

            //Rotate fcousPoint
            newFocusPointTop = CgU::rotatePointYAxis(currentAngle, focusPointTop);
            newFocusPointBottom = CgU::rotatePointYAxis(currentAngle, focusPointBottom);

            //Rotate normal endpoint
            newFaceNormalTopPoint = focusPointTop + faceNormalTop * 0.1f;
            newFaceNormalTopPoint = CgU::rotatePointYAxis(currentAngle, newFaceNormalTopPoint);
            newFaceNormalBottomPoint = focusPointBottom + faceNormalBottom * 0.1f;
            newFaceNormalBottomPoint = CgU::rotatePointYAxis(currentAngle, newFaceNormalBottomPoint);

            //Push polyline
            pushPoly(newFocusPointTop, newFaceNormalTopPoint);
            pushPoly(newFocusPointBottom, newFaceNormalBottomPoint);
        }
        last++;
    }

}





CgCone::~CgCone()
{
    polylineNormals.clear();

    m_vertices.clear();
    m_vertex_normals.clear();
    m_vertex_colors.clear();
    m_tex_coords.clear();
    m_triangle_indices.clear();
    m_face_normals.clear();
    m_face_colors.clear();
}

Cg::ObjectType CgCone::getType() const
{
    return m_type;
}

unsigned int CgCone::getID() const
{
    return m_id;
}

const std::vector<glm::vec3> &CgCone::getVertices() const
{
    return m_vertices;
}

const std::vector<glm::vec3> &CgCone::getVertexNormals() const
{
    return m_vertex_normals;
}

const std::vector<glm::vec3> &CgCone::getVertexColors() const
{
    return m_vertex_colors;
}

const std::vector<glm::vec2> &CgCone::getVertexTexCoords() const
{
    return m_tex_coords;
}

const std::vector<unsigned int> &CgCone::getTriangleIndices() const
{
    return m_triangle_indices;
}

const std::vector<glm::vec3> &CgCone::getFaceNormals() const
{
    return m_face_normals;
}

const std::vector<glm::vec3> &CgCone::getFaceColors() const
{
    return m_face_colors;
}

std::vector<CgLine *>* CgCone::getPolylineNormals()
{
    return &polylineNormals;
}

void CgCone::createFace(int p1, int p2, int p3)
{
    m_triangle_indices.push_back(p1);
    m_triangle_indices.push_back(p2);
    m_triangle_indices.push_back(p3);
}

void CgCone::pushPoly(glm::vec3 p1, glm::vec3 p2)
{
    CgLine* poly = new CgLine(idGen->getNextId());
    poly->addVertice(p1);
    poly->addVertice(p2);
    polylineNormals.push_back(poly);
}

const glm::vec3 CgCone::getColor() const
{
    return m_color;
}

void CgCone::setColor(const glm::vec3 &color)
{
    m_color = color;
}


